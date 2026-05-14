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
        printError(ERR_NEEDMOREPARAMS(parsing.front()));
		server.sendToClient(&client, ERR_NEEDMOREPARAMS(parsing.front()));
        return ;
    }
    std::string channelName = *(parsing.begin() + 1);
	std::string nickname = *(parsing.begin() + 2);

	if (!server.channelExists(channelName))
	{
    	printError(ERR_NOSUCHCHANNEL(channelName));
		server.sendToClient(&client, ERR_NOSUCHCHANNEL(channelName));
		return;
	}

	Channel *channel = server.getChannel(channelName);

    if (!channel->isOperator(&client))
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

    if (!channel->hasMember(targetClient))
	{
		printError(ERR_NOTONCHANNEL(channelName));
		server.sendToClient(&client, ERR_NOTONCHANNEL(channelName));
		return;
	}

    server.removeClientFromChannel(targetClient, channelName);
}
