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

	if (channel->isInviteOnly() && !channel->isOperator(&client))
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

	if (channel->hasMember(targetClient))
	{
		printError(ERR_USERONCHANNEL);
		return;
	}

	channel->addInvite(targetClient)
	//RPL_INVITING à ajouter
}
