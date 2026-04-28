#include "../../include/Command.hpp"

/*
**This function allows a cllient to invite another client into a channel
** The command does :
			Retrieve the arguments
			Extract nickname and channel
			Verify that channel et nickname exists
			Send an invitation
*/
void Command::invite(Message const &msg, Client &client, Server &server)
{    
	std::string arg = getArgument(msg.getMsg());

    if (isEmptyArg(arg))
    {
        printError(ERR_NEEDMOREPARAMS);
        return ;
    }

	std::string nickname = getTarget(arg);
	std::string channelName = getMessage(arg);

	if (channelName.empty())
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
		printError(ERR_NO);
		return;
	}

	Client *tagetClient = server.getClientbyNick(nickname);
	if(!tagetClient)
	{
		printError(ERR_NOSUCHNICK);
		return;
	}
}

// A finir plus tard