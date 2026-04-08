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

//void Server::setMapClients(std::map<int, Client*> _clients);
//void Server::setMapChannels(std::map<std::string, Channel*> _channels);


void    printMap(std::map<int, Client *> map)
{
    for (std::map<int, Client *>::iterator it = map.begin(); it != map.end(); ++it)
    {
        std::cout << "---  " << it->first << " " << it->second << " \n";
    }
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

    //getprotobyname("name of protocol")
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

void    Server::closeSockets()
{
    for (std::map<int, Client*>::iterator it = this->_clients.begin(); it != this->_clients.end(); it ++)
    {
        close(it->first);
    }
    close(this->_socket);
}

std::map<int, Client*>::iterator itoit(std::map<int, Client*> map, int i)
{
    std::map<int, Client*>::iterator it = map.begin();
    int j = 0;
    while (j < i)
    {
        it ++;
        j ++;
    }
    return (it);
}

void    Server::addClient()// struct pollfd *fds) //struct pollfd *fd) //int clientSocket, struct pollfd *fds, int nfds)
{
	//socklen_t			len;
	//struct sockaddr_in	clientAddr;

    int clientSocket = accept(this->_socket, NULL, NULL);//(struct sockaddr*)&clientAddr, &len);

    if (clientSocket < 0)
    {
        perror("accept failed");
        //return (-1);
        exit(EXIT_FAILURE);
    }

    this->_fds[this->_nfd].fd = clientSocket;
    this->_fds[this->_nfd].events = POLLIN;
    this->_nfd ++;

	//char	host[INET_ADDRSTRLEN];
	//inet_ntop(AF_INET, &clientAddr.sin_addr, host, INET_ADDRSTRLEN);

    Client  newClient(clientSocket);
    this->_clients.insert(this->_clients.end(), std::make_pair(clientSocket, &newClient));

    std::cout << "client added:\n";
    printMap(this->_clients);

    //return (clientSocket);
}

void    Server::removeClient(int i) //std::map<int, Client*>::iterator it)
{
    std::map<int, Client*>::iterator it = itoit(this->_clients, i);

    //close(it->first);
    this->_clients.erase(it);


	close(_fds[i].fd);
	_fds[i].fd = _fds[_nfd-1].fd;
	_fds[i].events = POLLIN;
	_fds[_nfd - 1].fd = -1;
    this->_nfd --;
}

void    Server::clientRequest(int i)//struct pollfd *fds, int i) //char *buffer, int i) //std::map<int, Client*>::iterator it)
{
    //std::map<int, Client*>::iterator    it = itoit(this->_clients, i);
    //std::cout << "here\n";
    //int                                 fd = it->second->getFd();
    int fd = this->_fds[i].fd;

    char    buffer[1024];
    ssize_t nbytes = recv(fd, buffer, sizeof(buffer), MSG_DONTWAIT);
    if (nbytes)
    {
        buffer[nbytes] = '\0';
        std::cout << YELLOW << "Message from client " << fd << " : " << DEFAULT << buffer << std::endl;
    }

    //std::map<int, Client*>::iterator    it = itoit(this->_clients, i);
    //std::cout << "it->second = " << it->second << std::endl;
    //int                                 fd = it->second->getFd();//it->second->getFd();
                    
    /*std::cout << YELLOW << "Message from client " << it->first << " : " << DEFAULT;
    bool mustCloseClient = false;
    while (true)
    {
        char    buffer[1024];
        ssize_t nbytes = recv(fd, buffer, sizeof(buffer), MSG_DONTWAIT); //this->clientRequest(buffer, i -1);
        if (nbytes < 0)
        {
            std::cout << "\nnbytes < 0\n";
            if (errno != EWOULDBLOCK)
            {
                perror(" recv() failed");
                mustCloseClient = true;
            }
            break;
        }
        else if (nbytes == 0)
        {
            std::cout << "nbytes = 0\n";
            mustCloseClient = true;
            break;
        }
        std::cout << buffer;
    }
    if (mustCloseClient)
    {
        std::cout << "must close\n";
        close(fds[i].fd);
        fds[i].fd = -1;
    }
    std::cout << "broke recv loop\n";*/
}

void    Server::run()
{
    //bool            mustCloseServ = false;
    //bool            mustCloseClient = false;
    //struct pollfd   fds[200];
    
    //ssize_t         nbytes;

    memset(this->_fds, 0, sizeof(this->_fds));
    this->_fds[0].events = POLLIN;
    this->_fds[0].fd = this->_socket;
    this->_nfd = 1;

    while (true)
    {
        //std::cout << "loop entered with currentSize of " << currentSize << "\n";
    
        int currentSize = this->_nfd;
        int ready = poll(this->_fds, currentSize, -1);
        if (ready < 0)
        {
            perror("poll() failed");
            break;
        }
        else if (ready == 0)
        {
            perror(" poll() timed out.");
            break;
        }
        
        for (int i = 0; i < currentSize; i ++)
        //for (std::map<int, Client*>::iterator it = this->_clients.begin(); it != this->_clients.end(); it ++)
        {
            std::cout << "i = " << i << " fds[i].revents = " << this->_fds[i].revents << " fds[i].fd = " << this->_fds[i].fd << " currentSize = " << currentSize << std::endl;

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
                    this->clientRequest(i);
                }
            }
            else if ((this->_fds[i].revents & POLLHUP) || (this->_fds[i].revents & POLLOUT))
            {
                this->removeClient(i -1);
                break;
            }
            /*else
            {
                perror("Unexpected revents.");
                mustCloseServ = true;
                break;
            }*/
        }
        std::cout << "broke for loop\n";
    }
    std::cout << "broke while serv on loop\n";
}