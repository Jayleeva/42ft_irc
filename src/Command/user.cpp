#include "../../include/Command.hpp"

/*
** The USER message is used at the beginning of connection to specify
   the username, hostname, servername and realname of the new user
**USER <username> <hostname> <servername> <realname>
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
