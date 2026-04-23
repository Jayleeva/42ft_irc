#include "../../include/Command.hpp"

/*
** PRIVMSG is used to send private messages between users.  <receiver>
   is the nickname of the receiver of the message.  <receiver> can also
   be a list of names or channels separated with commas
*/

void privmsg(Message const &msg, Client &client, Server &server)
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
}
