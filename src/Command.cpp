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
    (void)msg;
    (void)client;
    (void)server;
}
