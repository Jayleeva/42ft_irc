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

void    Server::addClient(struct pollfd *fds, int nfds)
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

    fds[nfds].fd = clientSocket;
    fds[nfds].events = POLLIN;

    std::cout << "client added:\n";
    printMap(this->_clients);
}

void    Server::removeClient(int i) //std::map<int, Client*>::iterator it)
{
    std::map<int, Client*>::iterator it = itoit(this->_clients, i);

    close(it->first);
    this->_clients.erase(it);
}

void    Server::clientRequest(int i) //std::map<int, Client*>::iterator it)
{
    std::map<int, Client*>::iterator it = itoit(this->_clients, i);

    int     fd = it->second->getFd();

    char    buffer[1024];

    /*ssize_t nbytes = recv(fd, buffer, sizeof(buffer), MSG_DONTWAIT);
    if (nbytes)
    {
        buffer[nbytes] = '\0';
        std::cout << YELLOW << "Message from client " << it->first << " : " << DEFAULT << buffer << std::endl;
    }*/

    ssize_t nbytes = recv(fd, buffer, sizeof(buffer), MSG_DONTWAIT);
    if (nbytes < 0)
    {
        perror("recv() failed");
        return ;
    }
    else if (nbytes == 0)
        return ;
    else
    {
        std::cout << YELLOW << "Message from client " << it->first << " : " << DEFAULT;
        while (nbytes)
        {
            if (nbytes < 0)
            {
                perror("recv() failed");
                return ;
            }
            else if (nbytes == 0)
            {
                buffer[0] = '\0';
                break;
            }
            else
            {
                buffer[nbytes] = '\0';
                std::cout << buffer << std::endl;
            }
            nbytes = recv(fd, buffer, sizeof(buffer), MSG_DONTWAIT);
        }
    }
}

void    Server::run()
{
    struct pollfd   fds[200];
    int             currentSize = 1;

    memset(fds, 0, sizeof(fds));
    fds[0].events = POLLIN;
    fds[0].fd = this->_socket;

    while (true)
    {
        //std::cout << "loop entered with currentSize of " << currentSize << "\n";
    
        int ready = poll(fds, currentSize, -1);
        if (ready == -1)
        {
            perror("poll failed");
            break;
        }
        else
        {
            //std::cout << "poll ongoing\n";

            for (int i = 0; i < currentSize; i ++)
            {
                try
                {
                    if (fds[i].revents & POLLIN)
                    {
                        if (fds[i].fd == this->_socket)
                        {
                            this->addClient(fds, currentSize);
                            currentSize ++;
                        }
                        else
                            this->clientRequest(i -1);
                    }
                    else if ((fds[i].revents & POLLHUP) || (fds[i].revents & POLLOUT))
                    {
                        this->removeClient(i -1);
                        currentSize --; // risque de changer l'ordre? normalement pas car map n'a pas de random access
                    }
                }
                catch (std::exception &e)
                {
                    printError(e.what());
                }
            }
        }
    }
}