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
        if (channel->hasMember(&client))
        {
            printError("already joined channel");
            return;
        }
        /*if (channel->HasBanKicked(&client))
        {
            printError(ERR_BANNEDFROMCHAN);
            return;
        }*/
        if (channel->getAccess().hasKey)
        {
            if (parsing.size() < 3)
            {
                printError(ERR_NEEDMOREPARAMS);
                return ;
            }
            if (*(parsing.begin() + 2) != channel->getAccess().key)
            {
                printError(ERR_BADCHANNELKEY);
                return ;
            }
        }
    }
    else
    {
        channel = server.createChannel(channelName);
        channel->addOperator(&client);
    }
    channel->addMember(&client);
}

/*
Server - Channels :

- bool channelExists
- getChannel
- createChannel
- joinClientToChannel
- removeClientFromChannelgetPassword()
*/
