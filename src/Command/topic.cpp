#include "../../include/Command.hpp"

void Command::topic(std::vector<std::string> parsing, Client &client, Server &server)
{
	std::vector<std::string>::iterator it = parsing.begin();

	if (parsing.size() < 2)
	{
		printError(ERR_NEEDMOREPARAMS);
		server.sendError(client, "461", ERR_NEEDMOREPARAMS);
		return;
	}

	it ++;
	std::string channelName = *it;
    if (server.channelExists(channelName) == false)
	{
		printError(ERR_NOSUCHCHANNEL);
		server.sendError(client, "403", ERR_NOSUCHCHANNEL);
		return;
	}
	Channel *chan = server.getChannel(channelName);
	if (chan->isOperator(&client) == false)
	{
		printError(ERR_CHANOPRIVSNEEDED);
		server.sendError(client, "482", ERR_CHANOPRIVSNEEDED);
		return;
	}

	it ++;
	std::string newTopic = *it;
	chan->setTopic(newTopic);
}