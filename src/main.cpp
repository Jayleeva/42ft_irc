#include "../include/Server.hpp"
#include "../include/Client.hpp"
#include "../include/Channel.hpp"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char **argv)
{
    Server serv;
    std::string password;
    int port;
    struct sockaddr_in addr;

    if (argc != 3)
    {
        std::cout << "Usage: ./ircserv <port> <password>" << std::endl;
        return (1);
    }

    password = argv[2];
    if (password.empty())
    {
        std::cout << "Password can't be empty." << std::endl;
        return (1);
    }
    if (password.length() > 510)
    {
        std::cout << "Password can't be longer than 510 chars (UTF-8)." << std::endl;
        return (1);
    }
    serv.setPassword(password);

    port = atoi(argv[1]);
    if (port < 0 || port > 65535)
    {
        std::cout << "Invalid port number. Available ports range from 0 to 65535. Suggested port: 6667" << std::endl;
        return (1);
    }
    std::cout << std::boolalpha;

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    ch.addMember(&c1);
    std::cout << "c1 in channel: " << ch.hasMember(&c1) << std::endl;

    ch.addMember(&c2);
    std::cout << "c2 in channel: " << ch.hasMember(&c2) << std::endl;

    serv.openSocket(&addr);
    serv.run();
    serv.closeSockets();

    return (0);
}