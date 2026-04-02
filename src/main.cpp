#include "../include/Client.hpp"
#include <iostream>

int main()
{
    std::cout << std::boolalpha;
    Client c(42);

    std::cout << "fd: " << c.getFd() << std::endl;
    std::cout << "registered: " << c.isRegistered() << std::endl;

    c.setNickname("lisa");
    c.setUsername("lili");
    c.setRegistered(true);
    c.addChannel("#general");

    std::cout << "nickname: " << c.getNickname() << std::endl;
    std::cout << "username: " << c.getUsername() << std::endl;
    std::cout << "registered: " << c.isRegistered() << std::endl;
    std::cout << "in #general: " << c.isInChannel("#general") << std::endl;

    c.removeChannel("#general");
    std::cout << "in #general: " << c.isInChannel("#general") << std::endl;

    return (0);
}