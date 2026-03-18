#include "../include/Server.hpp"

Server::Server() {};
Server::~Server() {};

int Server::getSocket() const
{
    return (this->socket);
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

void Server::openSocket(sockaddr_in *addr)
{
    this->socket = socket(AF_INET, SOCK_STREAM, 0);
    
    if (this->socket < 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (bind(this->socket, (struct sockaddr*)addr, sizeof(addr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(this->socket, 5) < 0)
    {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
}

void    Server::closeSocket()
{
    for (std::map<int, Client*>::iterator it = this->_clients.begin(); it != this->_clients.end(); it ++)
    {
        close(it->first);
    }
    close(this->socket);
}

void    Server::addClient()
{
	socklen_t			len;
	struct sockaddr_in	clientAddr;

    int clientSocket = accept(this->socket, (struct sockaddr*)&clientAddr, &len);

    if (clientSocket < 0)
    {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
    else
        this->_clients.insert({clientSocket, &Client(clientSocket)});
}

void    Server::removeClient(std::map<int, Client*>::iterator it)
{
    close(it->first);
    this->_clients.erase(it);
}


void    Server::clientRequest(std::map<int, Client*>::iterator it)
{
    char    buffer[1024];

    recv(it->first, buffer, sizeof(buffer), MSG_DONTWAIT);
    std::cout << "Message from client " << it->first << " : " << buffer << std::endl;
}

void    Server::run()
{
    pollfd  pfd[this->_clients.size()];

    std::map<int, Client*>::iterator it = this->_clients.begin();
    for (int i = 0; i < this->_clients.size(); i ++)
    {
        pfd[i].fd = it->first;
        pfd[i].events = POLLIN | POLLHUP | POLLOUT;
        //pfd[i].revents = 0;
        it ++;
    }
    
    while (true)
    {
        int ready = poll(pfd, this->_clients.size(), -1);
        if (ready == -1)
        {
            perror("poll failed");
            break;
        }
        else
        {
            std::map<int, Client*>::iterator it = this->_clients.begin();
            for (int i = 0; i < this->_clients.size(); i ++)
            {
                try
                {
                    if (pfd[i].revents & POLLIN)
                    {
                        if (pfd[i].fd == this->socket)
                            this->addClient();
                        else
                            this->clientRequest(it);
                    }
                    else if ((pfd[i].revents & POLLHUP) || (pfd[i].revents & POLLOUT))
                        this->removeClient(it);
                }
                catch (std::exception &e)
                {
                    std::cerr << "\033[0;31m" << e.what() << "\033[0m" << '\n';
                }
                it ++;
            }
        }
    }
}