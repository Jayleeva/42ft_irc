#include "../include/Command.hpp"

Command::Command()
{}

Command::Command(std::vector<std::string> parsing) : _parsing(parsing)
{
}

Command::~Command()
{}

std::vector<std::string> Command::getParsing() const
{
    return _parsing;
}

void    Command::setParsing(std::vector<std::string> parsing)
{
    _parsing = parsing;
}

void sendWelcome(std::vector<std::string> _parsing, Client &client)
{
    (void)_parsing;
    std::string cap = *(_parsing.begin() + 1) + " " + *(_parsing.begin() + 2);
    //std::string nickName = *(_parsing.begin());
    //std::string userName = *(_parsing.begin());
    //std::string hostName = *(_parsing.begin());

    std::string welcome = ":ircserv 001 " + cap; //" " + nickName + " " + userName; //+ "[!" + userName + "@" + hostName + "]";
    std::cout << welcome << std::endl;
    send(client.getFd(), welcome.c_str(), strlen(welcome.c_str()), 0);
}

void    pong(Client &client)
{
    std::string pong = "PONG"; 
    send(client.getFd(), pong.c_str(), strlen(pong.c_str()), 0);
}

void Command::execute(Client &client, Server &server)
{
    std::string _cmd = _parsing.front();

    if (_cmd == CMD_CAP)
        sendWelcome(_parsing, client);
    else if (_cmd == CMD_PASS)
        pass(_parsing, client, server.getPassword());
    else if (_cmd == CMD_NICK)
        nick(_parsing, client, server);
    else if (_cmd == CMD_USER)
        user(_parsing, client);
    else if (_cmd == CMD_JOIN)
        join(_parsing, client, server);
    else if (_cmd == CMD_MODE)
        mode(_parsing, client, server);
    else if (_cmd == "PING")
        pong(client);
    else
    {
        std::cout << "cmd = " << _cmd << std::endl;
        printError(ERR_CMD);
    }
}

