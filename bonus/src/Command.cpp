#include "../include/Command.hpp"

Command::Command()
{}

Command::Command(std::vector<std::string> parsing) : _parsing(parsing)
{}

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

    if (_cmd.empty())
    {
        printError(ERR_UNKNOWNCOMMAND(_cmd));
        server.sendToClient(&client, ERR_UNKNOWNCOMMAND(_cmd));
        return;
    }

    if (_cmd != CMD_PASS && _cmd != CMD_NICK && _cmd != CMD_USER && _cmd != CMD_CAP)
    {
        if (!client.isRegistered())
        {
            printError(ERR_NOTREGISTRED(client.getNickname()));
            server.sendToClient(&client, ERR_NOTREGISTRED(client.getNickname()));
            return;
        }
    }

    if (_cmd == CMD_CAP)
    {
        if (_parsing.size() >= 2 && _parsing[1] == "LS")
            server.sendToClient(&client, RPL_CAP(client.getNickname()));
        return ;
    }
    else if (_cmd == CMD_PASS)
        pass(_parsing, client, server);
    else if (_cmd == CMD_NICK)
        nick(_parsing, client, server);
    else if (_cmd == CMD_USER)
    {
        user(_parsing, client, server);
        if (client.isRegistered())
            server.sendToClient(&client, RPL_WELCOME(client.getNickname()));
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
        server.sendToClient(&client, RPL_PING(client.getNickname(), *(_parsing.begin() + 1)));
    else if (_cmd == CMD_QUIT)
        return ;
    else
    {
        printError(ERR_UNKNOWNCOMMAND(_cmd));
        server.sendToClient(&client, ERR_UNKNOWNCOMMAND(_cmd));
    }
}
