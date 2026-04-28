#include "../include/Command.hpp"

Command::Command() : _cmd("")
{}

Command::Command(const std::string& cmd) : _cmd(cmd)
{}

Command::~Command()
{}


std::string Command::getCmd() const
{
    return _cmd;
}

void Command::setCmd(const std::string& cmd)
{
    _cmd = cmd;
}

void Command::execute(Message const &msg, Client &client, Server &server)
{
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
        nick(msg, client, server);
    else if (_cmd == CMD_USER)
        user(msg, client, server);
    else if (_cmd == CMD_JOIN)
        join(msg, client, server);
    else if (_cmd == CMD_PART)
        part(msg, client, server);
    else if (_cmd == CMD_PRIVMSG)
        privmsg(msg, client, server);
    else
        printError(ERR_CMD);
}
