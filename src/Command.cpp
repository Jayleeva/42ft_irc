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
    std::string cap = *(_parsing.begin() + 1) + " " + *(_parsing.begin() + 2);

    std::string welcome = ":ircserv 001 " + cap;
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
    else if (_cmd == CMD_PING)
        pong(client);
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
    else
    {
        std::cout << "cmd = " << _cmd << std::endl;
        printError(ERR_CMD);
    }
}

