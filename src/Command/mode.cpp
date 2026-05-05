#include "../../include/Command.hpp"

void Command::mode(std::vector<std::string> parsing, Client &client, Server &server)
{
	std::vector<std::string>::iterator it = parsing.begin();

	if (parsing.size() < 3)
	{
		printError(ERR_NEEDMOREPARAMS);
		return;
	}

	it ++;
	std::string channelName = *it;
    if (server.channelExists(channelName) == false)
	{
		printError(ERR_NOSUCHCHANNEL);
		return;
	}
	Channel *chan = server.getChannel(channelName);
	if (chan->isOperator(&client) == false)
	{
		printError(ERR_CHANOPRIVSNEEDED);
		return;
	}

	it ++;
	std::string flag = *it;
	while (it != parsing.end())
	{
		if (flag == "-i")
		{
			if (chan->isInviteOnly())
				chan->setInviteOnly(false);
			else
				chan->setInviteOnly(true);
			//sendChannelRPL(chan, RPL_CHANNELMODEIS, client);
		}
		else if (flag == "-t")
		{
			if (chan->isTopicRestricted())
				chan->setTopicRestricted(false);
			else
				chan->setTopicRestricted(true);
			//sendChannelRPL(chan, RPL_CHANNELMODEIS, client);
		}
		else if (flag == "-k")
		{
			if (chan->hasKey() == true)
				chan->setKey("");
			else
			{
				it ++;
				if (it == parsing.end())
				{
					printError(ERR_NEEDMOREPARAMS);
					return;
				}
				std::string key = *it;
				chan->setKey(key);
			}
			//sendChannelRPL(chan, RPL_CHANNELMODEIS, client);
		}
		else if (flag == "-o")
		{
			it ++;
			if (it == parsing.end())
			{
				printError(ERR_NEEDMOREPARAMS);
				return;
			}
			std::string targetName = *it;
			int fd = findClientByName(server.getMapClients(), targetName);
			Client *target = server.getMapClients().find(fd)->second;
			if (chan->isOperator(target))
				chan->removeOperator(target);
			else
				chan->addOperator(target);
			//sendChannelRPL(chan, RPL_, client);
			//sendChannelRPL(chan, RPL_, target); //send to target ?
		}
		else if (flag == "-l")
		{
			if (chan->hasUserLimit())
				chan->removeUserLimit();
			else
			{
				it ++;
				if (it == parsing.end())
				{
					printError(ERR_NEEDMOREPARAMS);
					return;
				}
				std::string limit = *it;
				chan->setUserLimit(atoi(limit.c_str()));
			}
			//sendChannelRPL(chan, RPL_CHANNELMODEIS, client);
		}
		else
		{
			printError(ERR_UMODEUNKNOWNFLAG);
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