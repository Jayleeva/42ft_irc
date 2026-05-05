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

    std::string welcome = RPL_WELCOME + cap;
    std::cout << welcome << std::endl;
    send(client.getFd(), welcome.c_str(), strlen(welcome.c_str()), 0);
}

void    pong(Client &client)
{
    std::string pong = "PONG"; 
    send(client.getFd(), pong.c_str(), strlen(pong.c_str()), 0);
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

    if (_cmd == CMD_CAP)
        sendWelcome(_parsing, client);
    else if (_cmd == CMD_PING)
        pong(client);
    else if (_cmd == CMD_PASS)
        pass(_parsing, client, server.getPassword());
    if (_cmd.empty())
    {
        printError(ERR_CMD);
        return;
    }
    
    if (_cmd != CMD_PASS && _cmd != CMD_NICK && _cmd != CMD_USER)
    {
        if (!client.isRegistered())
        {
            printError(ERR_NOTREGISTERED);
            return;
        }
    }

    if (_cmd == CMD_PASS)
        pass(msg, client, server);
    else if (_cmd == CMD_NICK)
        nick(_parsing, client, server);
    else if (_cmd == CMD_USER)
        user(_parsing, client);
    else if (_cmd == CMD_JOIN)
        join(_parsing, client, server);
    else if (_cmd == CMD_MODE)
        mode(_parsing, client, server);
    else if (_cmd == CMD_TOPIC)
        topic(_parsing, client, server);
    else if (_cmd == CMD_PART)
        part(_cmd, client, server);
    else if (_cmd == CMD_PRIVMSG)
        privmsg(_cmd, client, server);
    else if (_cmd == CMD_INVITE)
        invite(_cmd, client, server);
    else if (_cmd == CMD_KICK)
        kick(_cmd, client, server);
    else if (_cmd == CMD_QUIT)
        return ;
    else
    {
        printError(_cmd + ERR_UNKNOWNCOMMAND);
    }
}
