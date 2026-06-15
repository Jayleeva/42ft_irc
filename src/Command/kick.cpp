#include "../../include/Command.hpp"

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
	std::string reason;

	reason = "Kicked";

	if (parsing.size() > 3)
	{
		reason.clear();
		++it;
		while (it != parsing.end())
		{
			if (!reason.empty())
				reason += " ";
			reason += *it;
			it++;
		}
		if (!reason.empty() && reason[0] == ':')
			reason.erase(0, 1);
	}

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

	server.sendKickConfirmation(&client, targetClient, channel, reason);
	server.removeClientFromChannel(targetClient, channel, false);
}