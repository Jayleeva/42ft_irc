#include "../../include/Command.hpp"

/*
**This function allows a cllient to invite another client into a channel
** The command does :
			Retrieve the arguments
			Extract nickname and channel
			Verify that channel et nickname exists
			Send an invitation
*/
void Command::invite(std::vector<std::string> parsing, Server &server)
{
	if (parsing.size() < 2)
    {
        printError(ERR_NEEDMOREPARAMS);
        return ;
    }

	std::string nickname = *(parsing.begin() + 1);
	std::string channelName = *(parsing.begin() + 2);

	int fd = findClientByName(server.getMapClients(), nickname);
	Client *target = server.getMapClients().find(fd)->second;
	target->addChannel(channelName);

	Channel *chan = server.getMapChannels().find(channelName)->second;
	chan->addMember(target);
}

// A finir plus tard