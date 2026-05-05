#include "../../include/Command.hpp"

/*
**The KICK command can be  used  to  forcibly  remove  a  user 
from  a channel.
** KICK <channel> <user>
*/

void Command::kick(Message const &msg, Client &client, Server &server)
{
    std::string arg = getArgument(msg.getMsg());

    if (isEmptyArg(arg))
    {
        printError(ERR_NEEDMOREPARAMS);
        return ;
    }

    std::string channelName = getTarget(arg);
	std::string nickname = getMessage(arg);

	if (isEmptyArg(channelName))
	{
		printError(ERR_NEEDMOREPARAMS);
		return ;
	}

    Channel *channel = server.getChannel(channelName);

	if (!channel)
	{
		printError(ERR_NOSUCHCHANNEL);
		return;
	}

    if (!channel->hasMember(&client))
    {
        printError(ERR_NOTONCHANNEL);
        return;
    }

    if (!channel->isOperator(&client))
    {		
        printError(ERR_CHANOPRIVSNEEDED);
		return;
    }

    Client *targetClient = server.getClientbyNick(nickname);

	if(!targetClient)
	{
		printError(ERR_NOSUCHNICK);
		return;
	}

    if (!channel->hasMember(targetClient))
	{
		printError(ERR_NOTONCHANNEL);
		return;
	}

    server.removeClientFromChannel(targetClient, channelName);
}
