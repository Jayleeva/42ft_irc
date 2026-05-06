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


void    printParsing(std::vector<std::string> parsing)
{
    std::cout << "parsing = ";
    for (std::vector<std::string>::iterator it = parsing.begin(); it != parsing.end(); it++)
    {
        std::cout << *it;
        if (it + 1 != parsing.end())
            std::cout << " ";
    }
    std::cout << std::endl;
}

void Command::execute(Client &client, Server &server)
{
    std::string _cmd = _parsing.front();

    if (_cmd.empty())
    {
        printError(ERR_UNKNOWNCOMMAND);
        return;
    }
    if (_cmd == CMD_CAP)
    {
        if (*(_parsing.begin() + 1) == "END\r\n")
            server.sendWelcome(client);
        else
            server.sendCap(client);
    }
    else if (_cmd == CMD_PASS)
        pass(_parsing, client, server.getPassword());   ///NOTE
    else if (_cmd == CMD_NICK)
        nick(_parsing, client, server);
    else if (_cmd == CMD_USER)
    {
        user(_parsing, client);
        //server.sendCap(client);
        server.sendWelcome(client);
    }
    else if (_cmd == CMD_JOIN)
        join(_parsing, client, server);
    else if (_cmd == CMD_MODE)
        mode(_parsing, client, server);
    else if (_cmd == CMD_TOPIC)
        topic(_parsing, client, server);
    else if (_cmd == CMD_PART)
        part(_parsing, client, server);
    else if (_cmd == CMD_PRIVMSG)
        privmsg(_parsing, client, server);
    else if (_cmd == CMD_INVITE)
        invite(_parsing, client, server);
    else if (_cmd == CMD_KICK)
        kick(_parsing, client, server);
    else if (_cmd == CMD_PING)
        server.pong(_parsing, client);
    else if (_cmd == CMD_QUIT)
        return ;
    else
    {
        printError(_cmd + ERR_UNKNOWNCOMMAND);
    }
}
