#include "../../include/Command.hpp"

/*
**This command allows to choose a client username.
**The server must:
    check that the username is not empty
    check if there is no invalid char
    check that it is not already taken by another client
    save this username in the `Client` object
*/

void Command::user(Message const &msg, Client &client, Server &server)
{
    std::string arg = getArgument(msg.getMsg());
    std::string username = getTarget(arg);

    if (isEmptyArg(username))
    {
        printError(ERR_NEEDMOREPARAMS);
        return ;
    }
    
    client.setUsername(username); 
    (void)server;
}
