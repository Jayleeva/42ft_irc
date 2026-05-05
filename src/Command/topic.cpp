#include "../../include/Command.hpp"

void Command::topic(std::vector<std::string> parsing, Client &client, Server &server)
{
	std::vector<std::string>::iterator it = parsing.begin();

	if (parsing.size() < 2)
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
	Channel *chan = server.getMapChannels().find(channelName)->second;
	if (chan->isOperator(&client) == false)
	{
		printError(ERR_CHANOPRIVSNEEDED);
		return;
	}

	it ++;
	std::string newTopic = *it;
	chan->setTopic(newTopic);
}