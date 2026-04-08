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

void    Server::addClient(int clientSocket) //struct pollfd *fds, int *nfds)
{
	/*socklen_t			len;
	struct sockaddr_in	clientAddr;

    int clientSocket = accept(this->_socket, (struct sockaddr*)&clientAddr, &len);

    if (clientSocket < 0)
    {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }*/


    ///fds[nfds].fd = clientSocket;
    //fds[nfds].events = POLLIN;



    Client  newClient(clientSocket);
    this->_clients.insert(this->_clients.end(), std::make_pair(clientSocket, &newClient));

    std::cout << "client added:\n";
    printMap(this->_clients);
}

void    Server::removeClient(int i) //std::map<int, Client*>::iterator it)
{
    std::map<int, Client*>::iterator it = itoit(this->_clients, i);

    close(it->first);
    this->_clients.erase(it);
}

void    Server::clientRequest(struct pollfd *fds, int i) //char *buffer, int i) //std::map<int, Client*>::iterator it)
{
    std::map<int, Client*>::iterator it = itoit(this->_clients, i);

    int     fd = it->second->getFd();

    /*ssize_t nbytes = recv(fd, buffer, sizeof(buffer), MSG_DONTWAIT);
    if (nbytes)
    {
        buffer[nbytes] = '\0';
        std::cout << YELLOW << "Message from client " << it->first << " : " << DEFAULT << buffer << std::endl;
    }*/

                    //std::map<int, Client*>::iterator    it = itoit(this->_clients, i);
                    //std::cout << "it->second = " << it->second << std::endl;
                    //int                                 fd = it->second->getFd();//it->second->getFd();
                    
                    std::cout << YELLOW << "Message from client " << it->first << " : " << DEFAULT;
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
                    std::cout << "broke recv loop\n";
}

void    Server::run()
{
    bool            mustCloseServ = false;
    //bool            mustCloseClient = false;
    struct pollfd   fds[200];
    int             currentSize = 1;
    //ssize_t         nbytes;

    memset(fds, 0, sizeof(fds));
    fds[0].events = POLLIN;
    fds[0].fd = this->_socket;

    while (!mustCloseServ)
    {
        //std::cout << "loop entered with currentSize of " << currentSize << "\n";
    
        int ready = poll(fds, currentSize, -1);
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
        {
            std::cout << "i = " << i << " fds[i].revents = " << fds[i].revents << " fds[i].fd = " << fds[i].fd << " currentSize = " << currentSize << std::endl;

            if (fds[i].revents & POLLIN)
            {
                if (fds[i].fd == this->_socket)
                {
                    int clientSocket = 0;
                    while (clientSocket != -1)
                    {
                        
                        //socklen_t			len;
                        //struct sockaddr_in	clientAddr;
                        clientSocket = accept(this->_socket, NULL, NULL); //(struct sockaddr*)&clientAddr, &len);
                        std::cout << "clientSocket = " << clientSocket << std::endl;
                        if (clientSocket < 0)
                        {
                            if (errno != EWOULDBLOCK)
                            {
                                perror("accept() failed");
                                mustCloseServ = true;
                            }
                            break;
                        }
                        addClient(clientSocket);
                        fds[currentSize].fd = clientSocket;
                        fds[currentSize].events = POLLIN;
                        currentSize ++;
                    }
                    std::cout << "broke accept loop\n";
                }
                else
                {
                    this->clientRequest(fds, i);
                }
            }
            else if ((fds[i].revents & POLLHUP) || (fds[i].revents & POLLOUT))
            {
                std::cout << "remove\n";
                this->removeClient(i -1);
                currentSize --; // risque de changer l'ordre? normalement pas car map n'a pas de random access
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