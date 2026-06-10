#include "../../include/Command.hpp"

/*
** The PART message causes the client sending the message to be removed
   from the list of active users for all given channels listed in the
   parameter string.
*/

void Command::part(std::vector<std::string> parsing, Client &client, Server &server)
{
    std::vector<std::string>::iterator it = parsing.begin();

    if (parsing.size() < 2)
    {
        printError(ERR_NEEDMOREPARAMS(parsing.front()));
		server.sendToClient(&client, ERR_NEEDMOREPARAMS(parsing.front()));
        return ;
    }

    std::string channelName = *(++it);

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

    std::string reason = "";
    while (++it != parsing.end())
    {
        reason.append(*it);
        if (it + 1 != parsing.end())
            reason.append(" ");
    }
    server.sendPartConfirmation(&client, channel, reason);
    server.removeClientFromChannel(&client, channel);
}

//vérifier si channel existe et si le client est membre du channel