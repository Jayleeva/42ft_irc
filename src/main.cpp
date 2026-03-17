#include "../include/Server.hpp"

int main (int argc, char **argv)
{
    Server          serv;
    t_addr          addr;
    std::string     password;

    if (argc != 3)
        return (1);

    addr.host = gethosbyname();
    addr.address = getaddrinfo();
    addr.port = htons(atoi(argv[1]));
    password = argv[2];

    serv.createSocket();
    return (0);
}