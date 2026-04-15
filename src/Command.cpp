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

<<<<<<< HEAD
void Command::execute(Message const &msg, Client &client, Server &server)
{
    if (_cmd == CMD_PASS)
        pass(msg, client, server);
    else if (_cmd == CMD_NICK)
        nick(msg, client, server);
    else if (_cmd == CMD_USER)
        user(msg, client, server);
    else if (_cmd == CMD_JOIN)
        join(msg, client, server);
    else
        printError(ERR_CMD);
}
=======
//void execute(Message const &msg, Client &client)
//{}
>>>>>>> 154afa2 (méthodes pour commandes + petite correction)
