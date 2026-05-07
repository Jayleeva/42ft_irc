#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <map>

#include <cerrno>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sstream>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <poll.h>


#include "Client.hpp"
#include "Channel.hpp"
#include "utils.hpp"

# define QUEUE_SIZE 5
# define MAXBYTES 512

class Server
{
    private:
        int             _socket;
		struct pollfd	_fds[SOMAXCONN];
		nfds_t		    _nfd;
        std::string     _password;
        std::map<int, Client*> _clients; // fd -> Client (index des clients connectés-> clients indexés par fd)
        std::map<std::string, Channel*> _channels; // nom de channel -> Channel (index des channels existants -> channels indexés par nom)
        std::string     _name;

    public:
        Server();
        ~Server();

        int                             getSocket() const;
        std::map<int, Client*>          getMapClients() const;
        std::map<std::string, Channel*> getMapChannels() const;
        void                            setPassword(std::string);
        std::string                     getPassword() const;
        std::string                     getName() const;

        void    openSocket(struct sockaddr_in *addr);
        void    closeSockets();
        void    clearClientsMap();
        void    run();
        void    addClient();
        void    removeClient(nfds_t i);
        void    removeFromAllChannels(Client *client);
        void    execClient(nfds_t i);

        void    execCmd(std::string input, int fd);

        bool    nicknameExists(const std::string &nickname) const;
        bool    channelExists(const std::string &name) const;
        Channel *getChannel(const std::string &name);
        Channel *createChannel(const std::string &name, const std::string key);
        void    joinClientToChannel(Client *client, const std::string &name, const std::string key);
        void    removeClientFromChannel(Client *client, const std::string &name);
        Client  *getClientByNick(const std::string &nickname);

        void    sendToClient(Client *target, std::string &message);
        void    sendMessageToClient(Client *sender, Client *target, const std::string &message);
        void    sendMessageToChannel(Client *sender, Channel *channel, const std::string &message);

        void    sendCap(Client &client);
        void    sendWelcome(Client &client);
        void    pong(std::vector<std::string> _parsing, Client &client);
};

void    printMap(std::map<int, Client *> map);

#endif