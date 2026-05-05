#include "../../include/Command.hpp"

/*
**This function allows a client to invite another client into a channel
** The command does :
			Retrieve the arguments
			Extract nickname and channel
			Verify that channel et nickname exists
			Send an invitation
*/
void Command::invite(std::vector<std::string> parsing, Client &client, Server &server) // NOTE : faire comme pour join, une methode dans server par ex?
{
	if (parsing.size() < 2)
    {
        printError(ERR_NEEDMOREPARAMS);
        return ;
    }

	std::string nickname = *(parsing.begin() + 1);
	std::string channelName = *(parsing.begin() + 2);

    if (server.channelExists(channelName) == false)
	{
		printError(ERR_NOSUCHCHANNEL);
		return;
	}

	Channel *channel = server.getChannel(channelName);

	if (!channel->isOperator(&client))
	{
		printError(ERR_CHANOPRIVSNEEDED);
		return;
	}

	/*if (!channel->hasMember(&client)) 	// NOTE : ne peut pas etre operateur de la channel si n'en est pas membre
	{
		printError(ERR_NOTONCHANNEL);
		return;
	}*/

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
