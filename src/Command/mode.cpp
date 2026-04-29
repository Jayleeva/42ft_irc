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
    if (channelExists(server.getMapChannels(), channelName) == false)
	{
		printError(ERR_NOSUCHCHANNEL);
		return;
	}
	Channel *chan = server.getMapChannels().find(channelName)->second;
	if (chan->hasOperator(&client) == false)
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
			if (chan->getAccess().inviteOnly == true)
				chan->setOnInvite(false);
			else
				chan->setOnInvite(true);
			//sendChannelRPL(chan, RPL_CHANNELMODEIS, client);
		}
		else if (flag == "-t")
		{
			if (chan->getTopic().restricted == true)
				chan->setRestricted(false);
			else
				chan->setRestricted(true);
			//sendChannelRPL(chan, RPL_CHANNELMODEIS, client);
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
			if (chan->hasOperator(target))
				chan->getOperators().erase(target);
			else
				chan->getOperators().insert(target);
			//sendChannelRPL(chan, RPL_, client);
			//sendChannelRPL(chan, RPL_, target); //send to target ?
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