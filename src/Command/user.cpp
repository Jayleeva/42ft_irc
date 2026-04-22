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

    size_t i = 0;
    while (i < arg.size() && arg[i] == ' ')
        i++;
    arg = arg.substr(i);

    if (isEmptyArg(arg))
    {
        printError(ERR_NEEDMOREPARAMS);
        return ;
    }

    size_t pos = arg.find(' ');
    if (pos != std::string::npos)
        arg = arg.substr(0, pos);
    
    client.setUsername(arg); 
    (void)server;
}
