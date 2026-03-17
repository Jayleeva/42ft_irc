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

void Server::setMapClients(std::map<int, Client*> _clients);
void Server::setMapChannels(std::map<std::string, Channel*> _channels);

void Server::openSocket(sockaddr_in *addr)
{
    int serverSocket;
    
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (bind(serverSocket, (struct sockaddr*)addr, sizeof(addr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(serverSocket, 5) < 0)
    {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
}

void    Server::closeSocket()
{
    for (std::map<int, Client*>::iterator it; it < this->_clients.end(); it ++)
    {
        close(it.first);
    }
    close(this->fd);
}

void    addClient()
{
	socklen_t			len;
	struct sockaddr_in	clientAddr;

    int clientSocket = accept(this->socket, (struct sockaddr*)clientAddr, &len);
    if (clientSocket < 0)
    {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
    else
        this->_clients.insert({clientSocket, ""});
}

void    removeClient(int i)
{
    close(this->_clients[i].first);
}

void    run()
{
    pollfd  pfd[this->_clients.size()];

    for (int i = 0; i < this->_clients.size(); i ++)
    {
        pfd[i].fd = this->_clients[i].first;
        pfd[i].events = POLLIN | POLLHUP | POLLOUT;
        //pfd[i].revents = 0;
    }
    
    while (true)
    {
        ready = poll(pfd, this->_clients.size(), -1);
        if (ready == -1)
        {
            perror("poll failed");
            break;
        }
        else
        {
            for (int i = 0; i < this->_clients.size(); i ++)
            {
                try
                {
                    if (pfd[i].revents & POLLIN)
                    {
                        if (pfd[i].fd == this->socket)
                            this->addClient();
                        else
                            clientRequest(i);
                    }
                    else if ((pfd[i].revents & POLLHUP) || (pfd[i].revents & POLLOUT))
                        this->removeClient(i);
                }
                catch (std::exception &e)
                {
                    std::cerr << "\033[0;31m" << e.what() << "\033[0m" << '\n';
                }
            }
        }
    }
}