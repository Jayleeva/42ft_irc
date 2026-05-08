#include "../../include/Command.hpp"

/*
**The KICK command can be  used  to  forcibly  remove  a  user 
from  a channel.
** KICK <channel> <user>
*/

void Command::kick(std::vector<std::string> parsing, Client &client, Server &server)
{
    if (parsing.size() < 3)
    {
        printError(ERR_NEEDMOREPARAMS);
		server.sendError(client, "461", ERR_NEEDMOREPARAMS);
        return ;
    }
    std::string channelName = *(parsing.begin() + 1);
	std::string nickname = *(parsing.begin() + 2);

	if (!server.channelExists(channelName))
	{
		printError(ERR_NOSUCHCHANNEL);
		server.sendError(client, "403", ERR_NOSUCHCHANNEL);
		return;
	}

	Channel *channel = server.getChannel(channelName);

    if (!channel->isOperator(&client))
    {		
        printError(ERR_CHANOPRIVSNEEDED);
		server.sendError(client, "482", ERR_CHANOPRIVSNEEDED);
		return;
    }

    Client *targetClient = server.getClientByNick(nickname);

	if(!targetClient)
	{
		printError(ERR_NOSUCHNICK);
		server.sendError(client, "401", ERR_NOSUCHNICK);
		return;
	}

    if (!channel->hasMember(targetClient))
	{
		printError(ERR_NOTONCHANNEL);
		server.sendError(client, "442", ERR_NOTONCHANNEL);
		return;
	}

    server.removeClientFromChannel(targetClient, channelName);
}
