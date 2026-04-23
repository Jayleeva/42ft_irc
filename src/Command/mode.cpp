#include "../../include/Command.hpp"

void Command::mode(std::vector<std::string> parsing, Client &client, Server &server)
{
	std::vector<std::string>::iterator it = parsing.begin();

	if (parsing.size() < 3)
	{
		printError("missing parameters");
		return;
	}

	it ++;
	std::string channelName = *it;
	if (!server.channelExists(channelName))
	{
		printError("channel does not exist");
		return;
	}
	if (client.getChannelStatus(channelName) != OPERATOR_STATUS)
	{
		printError("not an operator, cannot use /mode command");
		return;
	}

	Channel *chan = server.getMapChannels().find(channelName)->second;
	it ++;
	std::string flag = *it;
	while (it != parsing.end())
	{
		if (flag == "-i")
		{
			if (chan->getAccess().inviteOnly == true)
				chan->setOnInvite(false);
			else
				chan->setOnInvite(true);
		}
		else if (flag == "-t")
		{
			if (chan->getTopic().restricted == true)
				chan->setRestricted(false);
			else
				chan->setRestricted(true);
		}
		else if (flag == "-k")
		{
			if (chan->getAccess().hasKey == true)
				chan->setKey("");
			else
			{
				it ++;
				if (it == parsing.end())
				{
					printError("new key missing");
					return;
				}
				std::string key = *it;
				chan->setKey(key);
			}
		}
		else if (flag == "-o")
		{
			it ++;
			if (it == parsing.end())
			{
				printError("target missing");
				return;
			}
			std::string targetName = *it;
			int fd = findClientByName(server.getMapClients(), targetName);
			Client *target = server.getMapClients().find(fd)->second;
			if (target->getChannelStatus(channelName) == OPERATOR_STATUS)
				target->setChannelStatus(channelName, MEMBER_STATUS);
			else
				target->setChannelStatus(channelName, OPERATOR_STATUS);
		}
		else if (flag == "-l")
		{
			if (chan->getAccess().userLimit > 0)
				chan->setUserLimit(0);
			else
			{
				it ++;
				if (it == parsing.end())
				{
					printError("new limit missing");
					return;
				}
				std::string limit = *it;
				chan->setUserLimit(atoi(limit.c_str()));
			}
		}
		else
		{
			printError("flag does not exist");
			return;
		}
		it ++;
	}
}

/*
**i : Set/remove Invite-only channel
**t: Set/remove the restrictions of the TOPIC command to channel operators
**k: Set/remove the channel key (password)
**o: Give/take channel operator privilege
**l: Set/remove the user limit to channel
*/