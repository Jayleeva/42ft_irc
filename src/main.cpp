#include "../include/Server.hpp"
#include "../include/Client.hpp"
#include "../include/Channel.hpp"
#include <iostream>

#include "../include/Server.hpp"
#include "../include/utils.hpp"
// ports possibles pour IRC : 6665 - 6669, par defaut 6667

int main (int argc, char **argv)
{
    Server          serv;
    std::string     password;
    int             port;

    if (argc != 3)
        return (1);

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
        std::cout << "Invalid port number. Available ports range from 0 to 65535. Suggested port: 6697" << std::endl;
        return (1);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons((u_short)port);
    addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(addr.sin_zero), 0, 8);

    std::cout << "recieved port : " << port << std::endl;
    std::cout << "transformed port : " << addr.sin_port << std::endl;
    std::cout << "server address : " << addr.sin_addr.s_addr << std::endl;

    serv.openSocket(&addr);
    serv.run();
    serv.closeSockets();

    return (0);
}