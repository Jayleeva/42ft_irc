#include "../include/Server.hpp"
#include "../include/utils.hpp"

Server::Server() {};
Server::~Server() {};

int Server::getSocket() const
{
    return (this->_socket);
}

std::map<int, Client*> Server::getMapClients() const
{
    return (this->_clients);
}

std::map<std::string, Channel*> Server::getMapChannels() const
{
    return (this->_channels);
}

void    printMap(std::map<int, Client *> map)
{
    for (std::map<int, Client *>::iterator it = map.begin(); it != map.end(); ++it)
    {
        std::cout << "---  " << it->first << " " << it->second << " \n";
    }
}

void    Server::setPassword(std::string password)
{
    this->_password = password;
}

void Server::openSocket(struct sockaddr_in *addr)
{
    int opt = 1;
    this->_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (this->_socket < 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "is created\n";

    if (setsockopt(this->_socket, SOL_SOCKET, SO_REUSEADDR, (const char *) &opt, (sizeof(opt)))) //| SO_REUSEPORT
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    std::cout << "is set\n";

    if (bind(this->_socket, (struct sockaddr*)addr, sizeof(struct sockaddr)) < 0)
    {
        int errsv = errno;
        std::cout << "errno = " << errsv << std::endl;
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
 
    std::cout << "is bound\n";

    if (listen(this->_socket, QUEUE_SIZE) < 0)
    {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
    std::cout << "is listening\n";
}

void    Server::clearClientsMap()
{
    for (std::map<int, Client*>::iterator it = this->_clients.begin(); it != this->_clients.end(); it ++)
    {
        delete (it->second);
    }
    this->_clients.clear();
}

void    Server::closeSockets()
{
    for (size_t i = 0; i < this->_nfd; i++)
    {
        close(this->_fds[i].fd);
    }
    close(this->_socket);
    clearClientsMap();
}

void    Server::addClient()
{
    struct sockaddr_in  clientAddr;
    socklen_t           clientLen = sizeof(clientAddr);

    int clientSocket = accept(this->_socket, (struct sockaddr *)&clientAddr, &clientLen);
    if (clientSocket < 0)
    {
        perror("accept() failed");
        exit(EXIT_FAILURE);
    }

    this->_fds[this->_nfd].fd = clientSocket;
    this->_fds[this->_nfd].events = POLLIN;
    this->_nfd ++;

    Client  *newClient = new Client(clientSocket);
    newClient->setHostname(inet_ntoa(clientAddr.sin_addr));
    this->_clients.insert(this->_clients.end(), std::make_pair(clientSocket, newClient));

    std::cout << YELLOW << "Client " << clientSocket << " connected." << DEFAULT << std::endl;

    //(id) handshake [<option>=<valeur>,[<option>=<valeur>,...]]
    std::string message = this->_password;
    send(clientSocket, message.c_str(), strlen(message.c_str()), 0);
    //printMap(this->_clients);
}

void int_to_char(int num, char *result)
{
    int temp = num;
    int len = 0;

    while (temp > 0) {
        len++;
        temp /= 10;
    }

    for (int i = len - 1; i >= 0; i--) {
        result[i] = num % 10 + '0';
        num /= 10;
    }

    result[len] = '\0';
}

void    Server::removeClient(nfds_t i)
{
    std::map<int, Client*>::iterator    it;

    char result[1024];
    int_to_char(_fds[i].fd, result);

    it = this->_clients.find(_fds[i].fd);
    delete (it->second);
    this->_clients.erase(it);

	close(_fds[i].fd);
    std::cout << YELLOW << "Client " << _fds[i].fd << " disconnected." << DEFAULT << std::endl;

	_fds[i].fd = _fds[_nfd -1].fd;
	_fds[i].events = POLLIN;
	_fds[_nfd -1].fd = -1;
    _nfd --;

    std::string message = static_cast<std::string>(result) + " disconnected";
    for (nfds_t j = 1; j < _nfd; j ++)
    {
        std::cout << "'" << message << "'" << " sent to client " << _fds[j].fd << std::endl;
        send(_fds[j].fd, message.c_str(), strlen(message.c_str()), 0);
    }
}

void    Server::execClient(nfds_t i)
{
    int fd = this->_fds[i].fd;

    char    buffer[MAXBYTES];
    
    memset(buffer, '\0', sizeof(buffer));
    ssize_t nbytes = recv(fd, buffer, sizeof(buffer), MSG_DONTWAIT);
    if (nbytes)
    {
        buffer[nbytes] = '\0';
        std::cout << RED << nbytes << DEFAULT << std::endl;
        std::cout << buffer << std::endl;
        /*if (nbytes)
        {
            for (nfds_t j = 1; j < _nfd; j ++)
            {
                if (j != i)
                {
                    std::cout << "'" << buffer << "'" << " sent to client " << _fds[j].fd << " from client " << fd << std::endl;
                    send(_fds[j].fd, buffer, strlen(buffer), 0);
                }
            }
        }*/
        /*std::string cmd = getCmd(buffer);
        if (cmd == "JOIN")
        {
            std::string chan = getChan(buffer);
            if (_channels.find(chan) == _channels.end())
            {
                Channel newchan(chan);
                _channels.insert(_channels.end(), std::make_pair(chan, &newchan)))
            }
            _channels.find(chan)._members.insert(_clients(fd));
        }*/
    }
    if (nbytes == 0)
        this->removeClient(i);
}

void    Server::run()
{
    memset(this->_fds, 0, sizeof(this->_fds));
    this->_fds[0].events = POLLIN;
    this->_fds[0].fd = this->_socket;
    this->_nfd = 1;

    while (true)
    {   
        nfds_t currentSize = this->_nfd;
        int ready = poll(this->_fds, currentSize, -1);
        if (ready < 0)
        {
            perror("poll() failed");
            break;
        }
        else if (ready == 0)
        {
            perror(" poll() timed out."); // doit avoir un timeout ou pas?
            break;
        }
        
        for (nfds_t i = 0; i < currentSize; i ++)
        {
            if (this->_fds[i].revents == 0)
                continue;

            else if (this->_fds[i].revents & POLLIN)
            {
                if (this->_fds[i].fd == this->_socket)
                {
                    addClient();
                    break;
                }
                else
                {
                    this->execClient(i);
                }
            }
            else if ((this->_fds[i].revents & POLLHUP) || (this->_fds[i].revents & POLLOUT))
            {
                this->removeClient(i -1);
                break;
            }
        }
    }
}