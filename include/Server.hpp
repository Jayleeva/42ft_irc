#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <map>

#include <cerrno>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <poll.h>


#include "Client.hpp"
#include "Channel.hpp"

# define QUEUE_SIZE 5

/*struct pollfd 
{
    int   fd;         // file descriptor 
    short events;     // requested events 
    short revents;    // returned events 
};*/

class Server
{
    private:
        int _socket;
        std::map<int, Client*> _clients; // fd -> Client (index des clients connectés-> clients indexés par fd)
        std::map<std::string, Channel*> _channels; // nom de channel -> Channel (index des channels existants -> channels indexés par nom)

    public:
        Server();
        ~Server();

        int                             getSocket() const;
        std::map<int, Client*>          getMapClients() const;
        std::map<std::string, Channel*> getMapChannels() const;

        //void                            setMapClients(std::map<int, Client*> _clients);
        //void                            setMapChannels(std::map<std::string, Channel*> _channels);

        void    openSocket(struct sockaddr_in *addr);
        void    closeSockets();
        void    run();
        void    addClient(int clientSocket, struct pollfd *fds, int nfds);
        void    removeClient(int i); //std::map<int, Client*>::iterator it)
        ssize_t clientRequest(char *buffer, int i); //std::map<int, Client*>::iterator it)
};

void    printMap(std::map<int, Client *> map);

#endif