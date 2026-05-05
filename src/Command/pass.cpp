#include "../../include/Command.hpp"

/*
**The PASS command is used to set a 'connection password'.
** PASS <password>   
*/

void Command::pass(std::vector<std::string> parsing, Client &client, const std::string password)
{
    if (parsing.size() < 2)
    {
        printError(ERR_NEEDMOREPARAMS);
        return ;
    }

    std::string arg = *(parsing.begin() + 1);

    if (client.isRegistered())
    {
        printError(ERR_ALREADYREGISTRED);
        return;
    }

    if (arg != password) // fonction a creer
    {
        printError(ERR_PASSWDMISMATCH);
        return ;
    }

    client.setPassValid();
}