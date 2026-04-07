#include "../include/Server.hpp"
#include "../include/utils.hpp"
// ports possibles pour IRC : 6665 - 6669, par defaut 6667

// errno 22: EINVAL Invalid argument
// EINVAL in bind():
//    The socket is already bound to an address.
//    addrlen is wrong, or addr is not a valid address for this socket's domain.

int main (int argc, char **argv)
{
    Server          serv;
    std::string     password;
    int             port;

    if (argc != 3)
        return (1);

    password = argv[2];
    port = atoi(argv[1]);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons((u_short)port); //meme resultat que ntohs...
    addr.sin_addr.s_addr = INADDR_ANY;
    memset(&(addr.sin_zero), 0, 8);

    std::cout << "recieved port : " << port << std::endl;
    std::cout << "transformed port : " << addr.sin_port << std::endl;

    serv.openSocket(&addr);
    serv.run();
    serv.closeSockets();

    return (0);
}