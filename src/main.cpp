#include "../include/Server.hpp"

int main (int argc, char **argv)
{
    Server          serv;
    std::string     password;

    if (argc != 3)
        return (1);

    password = argv[2];

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[1]));
    addr.sin_addr.s_addr = INADDR_ANY;

    serv.openSocket(&addr);
    serv.run();
    serv.closeSocket();

    return (0);
}