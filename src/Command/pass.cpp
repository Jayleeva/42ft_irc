#include "../../include/Command.hpp"

/*
**The PASS command is used to set a 'connection password'.
** PASS <password>   
*/

void Command::pass(std::vector<std::string> parsing, Client &client, Server &server)
{
    if (parsing.size() < 2)
    {
        printError(ERR_NEEDMOREPARAMS);
        server.sendError(client, 461, ERR_NEEDMOREPARAMS);
        return ;
    }

    if (client.isRegistered())
    {
        printError(ERR_ALREADYREGISTRED);
        server.sendError(client, 462, ERR_ALREADYREGISTRED);
        return;
    }

    std::string arg = *(parsing.begin() + 1);
    arg = arg.substr(0, arg.find("\r\n"));
    std::cout << "password = '" << arg << "'" << std::endl;

    if (arg != server.getPassword()) // fonction a creer
    {
        printError(ERR_PASSWDMISMATCH);
        server.sendError(client, 464, ERR_PASSWDMISMATCH);
        return ;
    }
    client.setPassValid();
}