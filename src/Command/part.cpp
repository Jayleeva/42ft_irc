#include "../../include/Command.hpp"

/*
** The PART message causes the client sending the message to be removed
   from the list of active users for all given channels listed in the
   parameter string.
*/

void Command::part(Message const &msg, Client &client, Server &server)
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
    
    server.removeClientFromChannel(&client, arg);
}
