#include "../include/Server.hpp"

int main (int argc, char **argv)
{
    Server          serv;
    std::string     password;

    if (argc != 3)
        return (1);

    password = argv[2];

    std::cout << atoi(argv[1]) << std::endl;

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(atoi(argv[1])); //ntohs? meme resultat
    addr.sin_addr.s_addr = INADDR_ANY;

    std::cout << addr.sin_port << std::endl;

    serv.openSocket(&addr);
    serv.run();
    serv.closeSocket();

    return (0);
}