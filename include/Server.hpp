#ifndef SERVER_HPP
#define SERVER_HPP

#include <map>
#include <string>

#include <ws2def.h>
#include <poll.h>

#include "Client.hpp"
#include "Channel.hpp"

/*struct pollfd 
{
    int   fd;         // file descriptor 
    short events;     // requested events 
    short revents;    // returned events 
};*/

class Server
{
    private:
        int socket;
        std::map<int, Client*> _clients; // fd -> Client (index des clients connectés-> clients indexés par fd)
        std::map<std::string, Channel*> _channels; // nom de channel -> Channel (index des channels existants -> channels indexés par nom)

    public:
        Server();
        ~Server();

        int                             getSocket() const;
        std::map<int, Client*>          getMapClients() const;
        std::map<std::string, Channel*> getMapChannels() const;

        void                            setMapClients(std::map<int, Client*> _clients);
        void                            setMapChannels(std::map<std::string, Channel*> _channels);

        void    openSocket(t_addr &addr);
        void    closeSocket();
        void    addClient();
        void    removeClient(int i);
};

#endif