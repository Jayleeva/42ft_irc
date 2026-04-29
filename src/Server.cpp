#include "../include/Server.hpp"
#include "../include/utils.hpp"
#include "../include/Command.hpp"

Server::Server() {};
Server::~Server()
{
    std::map<int, Client*>::iterator it;

    it = _clients.begin();
    while (it != _clients.end())
    {
        delete it->second;
        it++;
    }
}

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

std::string Server::getPassword() const
{
    return (this->_password);
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

    Client  *newClient = new Client(this->_channels, clientSocket);
    newClient->setHostname(inet_ntoa(clientAddr.sin_addr));
    this->_clients.insert(this->_clients.end(), std::make_pair(clientSocket, newClient));

    std::cout << YELLOW << "Client " << clientSocket << " connected." << DEFAULT << std::endl;

    char    buffer[MAXBYTES];
    memset(buffer, '\0', sizeof(buffer));
    ssize_t nbytes = recv(clientSocket, buffer, sizeof(buffer), MSG_DONTWAIT);
    if (nbytes > 0)
    { 
        buffer[nbytes] = '\0';
        std::cout << "add " << RED << nbytes << DEFAULT << std::endl;
        std::cout << "buffer = " << buffer << std::endl;
    }
    //(id) handshake [<option>=<valeur>,[<option>=<valeur>,...]]
    //std::string message = this->_password;
    //send(clientSocket, message.c_str(), strlen(message.c_str()), 0);
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

void    Server::removeFromAllChannels(Client *client)
{
    for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); it ++)
    {
        if (it->second->hasMember(client))
        {
            if (it->second->hasOperator(client))
                it->second->removeOperator(client);
            it->second->removeMember(client);
        }
    }
}

void    Server::removeClient(nfds_t i)
{
    std::map<int, Client*>::iterator    it;

    char result[1024];
    int_to_char(_fds[i].fd, result);

    it = this->_clients.find(_fds[i].fd);
    if (it != this->_clients.end())
    {
        removeFromAllChannels(it->second);
        delete it->second;
        this->_clients.erase(it);
    }

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

Command parseCmd(std::string input)
{
    Command cmd;
    std::vector<std::string>	parsing;
	std::string			        element;
    std::stringstream 	        ss(input);

	while (getline(ss, element, ' '))
		parsing.push_back(element);
    
    cmd.setParsing(parsing);
    return (cmd);
}

void Server::execCmd(std::string input, int fd)
{
    Command cmd = parseCmd(input);

    cmd.execute(*(this->_clients.find(fd)->second), *this);
}

void    Server::execClient(nfds_t i)
{
    int fd = this->_fds[i].fd;

    char    buffer[MAXBYTES];
    
    memset(buffer, '\0', sizeof(buffer));
    ssize_t nbytes = recv(fd, buffer, sizeof(buffer), MSG_DONTWAIT);
    if (nbytes > 0)
    {
        buffer[nbytes] = '\0';

        execCmd(buffer, fd);
        
        std::cout << "exec " << RED << nbytes << DEFAULT << std::endl;
        std::cout << "buffer = " << buffer << std::endl;

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

bool Server::nicknameExists(const std::string &nickname) const
{
    std::map<int, Client*>::const_iterator it;

    it = _clients.begin();
    while (it != _clients.end())
    {
        if (it->second->getNickname() == nickname)
            return (true);
        it++;
    }
    return (false);
}

Channel *Server::createChannel(const std::string &name, Client *client)
{
    Channel *newChan = new Channel(name); // par defaut, tout est a false, 0 et ""

    this->_channels.insert(this->_channels.end(), std::make_pair(name, newChan));

    (void)client;
    //std::string trimmedName = newChan->getName().substr(1, strlen(newChan->getName().c_str())); // essayer d'enlever la diese
    /*std::string msg = " " + name + RPL_NOTOPIC; // find right command
    send(client->getFd(), msg.c_str(), strlen(msg.c_str()), 0);*/
    return (newChan);
}

void    Server::removeChannel(const std::string &name)
{
    this->_channels.erase(name);

    for (std::map<int, Client*>::iterator it = this->_clients.begin(); it != this->_clients.end(); it ++)
    {
        it->second->removeChannel(name);
    }
}

