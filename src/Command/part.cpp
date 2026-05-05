#include "../../include/Command.hpp"

/*
** The PART message causes the client sending the message to be removed
   from the list of active users for all given channels listed in the
   parameter string.
*/

void Command::part(Message const &msg, Client &client, Server &server)
{
    std::string arg = getArgument(msg.getMsg());
    std::string channel = getTarget(arg);

    if (isEmptyArg(channel))
    {
        printError(ERR_NEEDMOREPARAMS);
        return ;
    }
    
    server.removeClientFromChannel(&client, channel);
}
