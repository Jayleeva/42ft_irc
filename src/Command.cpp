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

void Command::execute(Client &client, Server &server)
{
    std::string _cmd = _parsing.front();

    if (_cmd == CMD_PASS)
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
        printError(ERR_CMD);
}

