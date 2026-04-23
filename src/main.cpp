#include "../include/Client.hpp"
#include "../include/Channel.hpp"
#include <iostream>

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
    if (password.empty())
    {
        std::cout << "Password can't be empty." << std::endl;
        std::exit(1);
    }
    else if (password.length() > 510)
    {
        std::cout << "Password can't be longer than 510 chars (UTF-8)." << std::endl;
        std::exit(1);
    }
    serv.setPassword(password);
    port = atoi(argv[1]);
	if (port < 0 || port > 65535) 
    {
		std::cout << "Invalid port number. Available ports range from 0 to 65535. Suggested port: 6667" << std::endl;
        std::exit(1);
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

/*int main()
{
    Client c1(42);
    Client c2(43);
    Channel ch("#general");

    c1.setNickname("lisa");
    c2.setNickname("chester");

    std::cout << std::boolalpha;

    std::cout << "channel name: " << ch.getName() << std::endl;
    std::cout << "c1 in channel: " << ch.hasMember(&c1) << std::endl;

    ch.addMember(&c1);
    std::cout << "c1 in channel: " << ch.hasMember(&c1) << std::endl;

    ch.addMember(&c2);
    std::cout << "c2 in channel: " << ch.hasMember(&c2) << std::endl;

    ch.removeMember(&c1);
    std::cout << "c1 in channel: " << ch.hasMember(&c1) << std::endl;

    return 0;
}*/