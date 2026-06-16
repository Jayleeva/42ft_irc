#include "../../include/Command.hpp"

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
    
    server.removeClientFromChannel(&client, channel, true);
}
