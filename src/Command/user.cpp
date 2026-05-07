#include "../../include/Command.hpp"

/*
** The USER message is used at the beginning of connection to specify
   the username, hostname, servername and realname of the new user
**USER <username> <hostname> <servername> <realname>
*/

void Command::user(std::vector<std::string> parsing, Client &client)
{
    if (parsing.size() < 2)
    {
        printError(ERR_NEEDMOREPARAMS);
        return ;
    }

    if (!client.hasPass())
    {
        printError(ERR_PASSWDMISMATCH);
        return ;
    }

    std::string arg = *(parsing.begin() + 1);

    client.setUsername(arg);
}
