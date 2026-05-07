#include "../../include/Command.hpp"

/*
**This function allows a client to invite another client into a channel
** The command does :
			Retrieve the arguments
			Extract nickname and channel
			Verify that channel et nickname exists
			Send an invitation
*/
void Command::invite(std::vector<std::string> parsing, Client &client, Server &server)
{
	if (parsing.size() < 2)
    {
        printError(ERR_NEEDMOREPARAMS);
        return ;
    }

	(void)client; // verifier si le client qui fait la demande est operateur de la channel

	std::string nickname = *(parsing.begin() + 1);
	std::string channelName = *(parsing.begin() + 2);

    if (!server.channelExists(channelName))
	{
    	printError(ERR_NOSUCHCHANNEL);
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

	Client *targetClient = server.getClientByNick(nickname);
	if(!targetClient)
	{
		printError(ERR_NOSUCHNICK);
		return;
	}

	if (!channel->hasMember(targetClient))
	{
		printError(ERR_USERONCHANNEL);
		return;
	}

	channel->invite(targetClient);
	//RPL_INVITING à ajouter
}
