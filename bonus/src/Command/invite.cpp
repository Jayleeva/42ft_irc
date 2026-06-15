#include "../../include/Command.hpp"

void Command::invite(std::vector<std::string> parsing, Client &client, Server &server)
{
	if (parsing.size() < 3 || parsing[1][0] == '#' || parsing[2][0] != '#')
    {
        printError(ERR_NEEDMOREPARAMS(parsing.front()));
		server.sendToClient(&client, ERR_NEEDMOREPARAMS(parsing.front()));
        return;
    }

	std::string nickname = *(parsing.begin() + 1);
	std::string channelName = *(parsing.begin() + 2);

    if (!server.channelExists(channelName))
	{
    	printError(ERR_NOSUCHCHANNEL(channelName));
		server.sendToClient(&client, ERR_NOSUCHCHANNEL(channelName));
    	return;
	}

	Channel *channel = server.getChannel(channelName);

	if (!channel)
	{
    	printError(ERR_NOSUCHCHANNEL(channelName));
		server.sendToClient(&client, ERR_NOSUCHCHANNEL(channelName));
		return;
	}

	if (!channel->hasMember(&client))
	{
		printError(ERR_NOTONCHANNEL(channelName));
		server.sendToClient(&client, ERR_NOTONCHANNEL(channelName));
		return;
	}

	if (channel->isInviteOnly() && !channel->isOperator(&client))
	{
		printError(ERR_CHANOPRIVSNEEDED(channelName));
		server.sendToClient(&client, ERR_CHANOPRIVSNEEDED(channelName));
		return;
	}

	Client *targetClient = server.getClientByNick(nickname);
	if(!targetClient)
	{
		printError(ERR_NOSUCHNICK(nickname));
		server.sendToClient(&client, ERR_NOSUCHNICK(nickname));
		return;
	}

	if (channel->hasMember(targetClient))
	{
		printError(ERR_USERONCHANNEL(nickname, channelName));
		server.sendToClient(&client, ERR_USERONCHANNEL(nickname, channelName));
		return;
	}

	channel->invite(targetClient);

	server.sendToClient(&client, RPL_INVITING(client.getNickname(), nickname, channel->getName()));
	server.sendToClient(targetClient, RPL_INVITING(client.getNickname(), nickname, channel->getName()));
}
