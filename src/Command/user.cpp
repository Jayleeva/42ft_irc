#include "../../include/Command.hpp"

/*
**This command allows to choose a client username.
**The server must:
    check that the username is not empty
    check that it is not already taken by another client
    save this username in the `Client` object
*/

void Command::user(Message const &msg, Client &client)
{
    std::string arg = getArgument(msg.getMsg());

    if (isEmptyArg(arg))
    {
        printError(ERR_NEEDMOREPARAMS);
        return ;
    }
    client.setUsername(arg); 
}

/*
** à faire -> fonction Realname
*/