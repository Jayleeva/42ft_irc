#include "../../include/Command.hpp"

void Command::topic(std::vector<std::string> parsing, Client &client, Server &server)
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

	if (parsing.size() > 2)
	{
		if (chan->isOperator(&client) == false)
		{
			printError(ERR_CHANOPRIVSNEEDED(channelName));
			server.sendToClient(&client, ERR_CHANOPRIVSNEEDED(channelName));
			return;
		}
		std::string newTopic = "";
		while (++it != parsing.end())
		{
			newTopic.append(*(it));
			if (it + 1 != parsing.end())
				newTopic.append(" ");
		}
		chan->setTopic(newTopic);
		server.sendToClient(&client, RPL_TOPIC(chan->getName(), chan->getTopic()));
	}
	else
	{
		if (chan->isTopicRestricted())
		{
			if (chan->isOperator(&client) == false)
			{
				printError(ERR_CHANOPRIVSNEEDED(channelName));
				server.sendToClient(&client, ERR_CHANOPRIVSNEEDED(channelName));
				return;
			}
		}
		if (chan->hasTopic())
			server.sendToClient(&client, RPL_TOPIC(chan->getName(), chan->getTopic()));
		else
			server.sendToClient(&client, RPL_NOTOPIC(chan->getName()));
	}
}