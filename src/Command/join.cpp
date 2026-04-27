#include "../../include/Command.hpp"

/*
**The JOIN command is used by client to start listening a specific
   channel
*/

void Command::join(std::vector<std::string> parsing, Client &client, Server &server)
{
    if (parsing.size() < 2)
    {
        printError(ERR_NEEDMOREPARAMS);
        return ;
    }
	std::string channelName = *(parsing.begin() + 1);
    
    Channel *channel;
    std::string check = findChannel(server.getMapChannels(), channelName);
    if (!check.empty())
    {
        if (client.getChannelStatus(channelName) == KICKED_STATUS)
        {
            printError("kicked from channel");
            return;
        }
        if (client.getChannelStatus(channelName) == MEMBER_STATUS || client.getChannelStatus(channelName) == OPERATOR_STATUS)
        {
            printError("already joined channel");
            return;
        }
        channel = server.getMapChannels().find(channelName)->second;
        channel->addMember(&client);
        client.setChannelStatus(channelName, MEMBER_STATUS); // par defaut, a le statut de membre
    }
    else
    {
        channel = server.createChannel(channelName);
        channel->addMember(&client);
        client.setChannelStatus(channel->getName(), OPERATOR_STATUS); // par defaut, createur a statut d-operateur
    }

}

/*
Server - Channels :

- bool channelExists
- getChannel
- createChannel
- joinClientToChannel
- removeClientFromChannelgetPassword()
*/
