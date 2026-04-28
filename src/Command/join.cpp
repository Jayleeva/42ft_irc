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
    if (channelExists(server.getMapChannels(), channelName) == true)
    {
        channel = server.getMapChannels().find(channelName)->second;
        if (channel->hasMember(&client) || channel->hasOperator(&client))
        {
            printError("already joined channel");
            return;
        }
        /*if (client.getChannelStatus(channelName) == KICKED_STATUS)
        {
            printError("kicked from channel");
            return;
        }*/
        channel->addMember(&client);
    }
    else
    {
        channel = server.createChannel(channelName);
        channel->addOperator(&client);
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
