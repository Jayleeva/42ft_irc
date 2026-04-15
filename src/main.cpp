#include "../include/Client.hpp"
#include "../include/Channel.hpp"
#include <iostream>

int main()
{
    Client c1(42);
    Client c2(43);
    Channel ch("#general");

    c1.setNickname("lisa");
    c2.setNickname("chester");

<<<<<<< HEAD
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
=======
    std::cout << std::boolalpha;
>>>>>>> 154afa2 (méthodes pour commandes + petite correction)

    std::cout << "channel name: " << ch.getName() << std::endl;
    std::cout << "c1 in channel: " << ch.hasMember(&c1) << std::endl;

<<<<<<< HEAD
    std::cout << "recieved port : " << port << std::endl;
    std::cout << "transformed port : " << addr.sin_port << std::endl;
    std::cout << "server address : " << addr.sin_addr.s_addr << std::endl;
=======
    ch.addMember(&c1);
    std::cout << "c1 in channel: " << ch.hasMember(&c1) << std::endl;
>>>>>>> 154afa2 (méthodes pour commandes + petite correction)

    ch.addMember(&c2);
    std::cout << "c2 in channel: " << ch.hasMember(&c2) << std::endl;

    ch.removeMember(&c1);
    std::cout << "c1 in channel: " << ch.hasMember(&c1) << std::endl;

    return 0;
}