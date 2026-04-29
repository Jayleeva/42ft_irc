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

    if (channelExists(server.getMapChannels(), channelName) == false)
	{
		printError(ERR_NOSUCHCHANNEL);
		return;
	}
	Channel *chan = server.getMapChannels().find(channelName)->second;

	int fd = findClientByName(server.getMapClients(), nickname);
	Client *target = server.getMapClients().find(fd)->second;

	if (chan->hasMember(target))
	{
		printError(ERR_USERONCHANNEL);
		return;
	}
	chan->addMember(target);
}