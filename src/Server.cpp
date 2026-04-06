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

void Server::openSocket(struct sockaddr_in *addr)
{
    int opt = 0;
    this->_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (this->_socket < 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "is created\n";

    //getprotobyname("name of protocol")
    if (setsockopt(this->_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, (const char *) &opt, (sizeof(opt)))) 
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

void    Server::closeSocket()
{
    for (std::map<int, Client*>::iterator it = this->_clients.begin(); it != this->_clients.end(); it ++)
    {
        close(it->first);
    }
    close(this->_socket);
}

void    Server::addClient()
{
	socklen_t			len;
	struct sockaddr_in	clientAddr;

    int clientSocket = accept(this->_socket, (struct sockaddr*)&clientAddr, &len);

    if (clientSocket < 0)
    {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
    Client  newClient(clientSocket);
    this->_clients.insert(this->_clients.end(), std::make_pair(clientSocket, &newClient));
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
    std::cout << YELLOW << "Message from client " << it->first << " : " << DEFAULT << buffer << std::endl;
}

void    Server::run()
{
    pollfd  pfd[this->_clients.size()];

    int i = 0;
    for (std::map<int, Client*>::iterator it = this->_clients.begin(); it != this->_clients.end(); it ++)
    {
        pfd[i].fd = it->first;
        pfd[i].events = POLLIN | POLLHUP | POLLOUT;
        //pfd[i].revents = 0;
        i ++;
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
            int i = 0;
            for (std::map<int, Client*>::iterator it = this->_clients.begin(); it != this->_clients.end(); it ++)
            {
                try
                {
                    if (pfd[i].revents & POLLIN)
                    {
                        if (pfd[i].fd == this->_socket)
                            this->addClient();
                        else
                            this->clientRequest(it);
                    }
                    else if ((pfd[i].revents & POLLHUP) || (pfd[i].revents & POLLOUT))
                        this->removeClient(it);
                }
                catch (std::exception &e)
                {
                    printError(e.what());
                }
                i ++;
            }
        }
    }
}