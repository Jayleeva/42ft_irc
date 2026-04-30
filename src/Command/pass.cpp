#include "../../include/Command.hpp"

/*
**The PASS command is used to set a 'connection password'.
** PASS <password>   
*/

void Command::pass(Message const &msg, Client &client, Server &server)
{
    std::cout << "PASS handler called" << std::endl;

    std::string arg = getArgument(msg.getMsg());
    std::string password = getTarget(arg);

    if (isEmptyArg(password))
    {
        printError(ERR_NEEDMOREPARAMS);
        return ;
    }

    if (client.isRegistered())
    {
        printError(ERR_REGISTRED);
        return;
    }

    if (password != server.getPassword())
    {
        printError(ERR_PASSWDMISMATCH);
        return ;
    }

    client.setPassValid();
}