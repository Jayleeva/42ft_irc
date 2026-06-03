#include "../../include/Command.hpp"

void Command::mode(std::vector<std::string> parsing, Client &client, Server &server)
{
	std::vector<std::string>::iterator it = parsing.begin();

	if (parsing.size() < 2)
	{
        printError(ERR_NEEDMOREPARAMS(parsing.front()));
		server.sendToClient(&client, ERR_NEEDMOREPARAMS(parsing.front()));
		return;
	}

	it ++;
	std::string channelName = *it;
    if (server.channelExists(channelName) == false)
	{
    	printError(ERR_NOSUCHCHANNEL(channelName));
		server.sendToClient(&client, ERR_NOSUCHCHANNEL(channelName));
		return;
	}
	Channel *chan = server.getChannel(channelName);
	if (parsing.size() == 2)
	{
		std::string mode = chan->getMode();
		std::string params = chan->getModeParams();
		server.sendToClient(&client, RPL_CHANNELMODEIS(channelName, mode, params));
		return;
	}
	if (chan->isOperator(&client) == false)
	{
		printError(ERR_CHANOPRIVSNEEDED(channelName));
		server.sendToClient(&client, ERR_CHANOPRIVSNEEDED(channelName));
		return;
	}

	it ++;
	std::string flag = *it;
	while (it != parsing.end())
	{
		if (flag == "-i")
		{
			chan->setInviteOnly(!chan->isInviteOnly());
			server.sendNewParams(*chan, &client, flag);
		}
		else if (flag == "-t")
		{
			chan->setTopicRestricted(!chan->isTopicRestricted());
			server.sendNewParams(*chan, &client, flag);
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
					printError(ERR_NEEDMOREPARAMS(parsing.front()));
					server.sendToClient(&client, ERR_NEEDMOREPARAMS(parsing.front()));
					return;
				}
				std::string key = *it;
				chan->setKey(key);
			}
			server.sendNewParams(*chan, &client, flag);
		}
		else if (flag == "-o")
		{
			it ++;
			if (it == parsing.end())
			{
				printError(ERR_NEEDMOREPARAMS(parsing.front()));
				server.sendToClient(&client, ERR_NEEDMOREPARAMS(parsing.front()));
				return;
			}
			std::string targetName = *it;
			Client *target = server.getClientByNick(targetName);
			if (chan->isOperator(target))
				chan->removeOperator(target);
			else
				chan->addOperator(target);
			server.sendNewParams(*chan, &client, flag);
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
					printError(ERR_NEEDMOREPARAMS(parsing.front()));
					server.sendToClient(&client, ERR_NEEDMOREPARAMS(parsing.front()));
					return;
				}
				std::string limit = *it;
				chan->setUserLimit(atoi(limit.c_str()));
			}
			server.sendNewParams(*chan, &client, flag);
		}
		else
		{
			printError(ERR_UNKNOWNMODE(flag));
			server.sendToClient(&client, ERR_UNKNOWNMODE(flag));
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