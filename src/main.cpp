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
}