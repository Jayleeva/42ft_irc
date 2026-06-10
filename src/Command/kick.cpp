#include "../../include/Command.hpp"

/*
**The KICK command can be  used  to  forcibly  remove  a  user 
from  a channel.
** KICK <channel> <user>
*/

void Command::kick(std::vector<std::string> parsing, Client &client, Server &server)
{
	std::vector<std::string>::iterator it = parsing.begin();

    if (parsing.size() < 3)
    {
        printError(ERR_NEEDMOREPARAMS(parsing.front()));
		server.sendToClient(&client, ERR_NEEDMOREPARAMS(parsing.front()));
        return ;
    }
    std::string channelName = *(++it);
	std::string nickname = *(++it);

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

	std::string reason = "";
	while (++it != parsing.end())
	{
		reason.append(*(it));
		if (it + 1 != parsing.end())
			reason.append(" ");
	}
    
	server.sendKickConfirmation(&client, channel, nickname, reason);
	server.removeClientFromChannel(targetClient, channel);
}
