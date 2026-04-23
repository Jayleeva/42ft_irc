#include "../../include/Command.hpp"

void Command::mode(Message const &msg, Client &client, Server &server)
{
	std::string channelName;
	char		flag;
	std::string	key;
	int			limit;
	std::string	targetName;

	if (client.getChannelStatus(channelName) != OPERATOR_STATUS)
	{
		printError("not an operator, cannot use mode");
		return;
	}
	
	Channel *chan = server.getMapChannels().find(channelName)->second;
	if (flag == 'i')
	{
		if (chan->getAccess().inviteOnly == true)
			chan->setOnInvite(false);
		else
			chan->setOnInvite(true);
	}
	else if (flag == 't')
	{
		if (chan->getTopic().restricted == true)
			chan->setRestricted(false);
		else
			chan->setRestricted(true);
	}
	else if (flag == 'k')
	{
		if (chan->getAccess().hasKey == true)
			chan->setKey("");
		else
			chan->setKey(key);
	}
	else if (flag == 'o')
	{
		int fd = findClientByName(server.getMapClients(), targetName);
		Client *target = server.getMapClients().find(fd)->second;
		if (target->getChannelStatus(channelName) == OPERATOR_STATUS)
			target->setChannelStatus(channelName, MEMBER_STATUS);
		else
			target->setChannelStatus(channelName, OPERATOR_STATUS);
	}
	else if (flag == 'l')
	{
		if (chan->getAccess().userLimit > 0)
			chan->setUserLimit(0);
		else
			chan->setUserLimit(limit);
	}
}

/*
**i : Set/remove Invite-only channel
**t: Set/remove the restrictions of the TOPIC command to channel operators
**k: Set/remove the channel key (password)
**o: Give/take channel operator privilege
**l: Set/remove the user limit to channel
*/