#include "../../include/Command.hpp"

/*
** The PART message causes the client sending the message to be removed
   from the list of active users for all given channels listed in the
   parameter string.
*/

void Command::part(std::vector<std::string> parsing, Client &client, Server &server)
{
    if (parsing.size() < 2)
    {
        printError(ERR_NEEDMOREPARAMS(parsing.front()));
		server.sendToClient(&client, ERR_NEEDMOREPARAMS(parsing.front()));
        return ;
    }

    std::string channelName = *(parsing.begin() + 1);

    Channel *channel = server.getChannel(channelName);

	if (!channel)
	{
		printError(ERR_NOSUCHCHANNEL);
		return;
	}

    if (!channel->hasMember(&client))
	{
		printError(ERR_NOTONCHANNEL);
		return;
	}
    
    server.removeClientFromChannel(&client, channelName);
}

//vérifier si channel existe et si le client est membre du channel