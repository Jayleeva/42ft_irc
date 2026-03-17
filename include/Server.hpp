#ifndef SERVER_HPP
#define SERVER_HPP

#include <map>
#include <string>
#include "Client.hpp"
#include "Channel.hpp"

typedef struct s_addr
{
    void    host;
    void    address;
    void    port;  
}           t_addr;

class Server
{
    private:
        std::map<int, Client*> _clients; // fd -> Client (index des clients connectés-> clients indexés par fd)
        std::map<std::string, Channel*> _channels; // nom de channel -> Channel (index des channels existants -> channels indexés par nom)

    public:
        Server();
};

#endif