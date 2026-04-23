#include "../../include/Command.hpp"

/*
**The JOIN command is used by client to start listening a specific
   channel
*/

void Command::join(Message const &msg, Client &client, Server &server)
{
	std::string arg = getArgument(msg.getMsg());

    size_t i = 0;
    while (i < arg.size() && arg[i] == ' ')
        i++;
    arg = arg.substr(i);

    if (isEmptyArg(arg))
    {
        printError(ERR_NEEDMOREPARAMS);
        return ;
    }

    size_t pos = arg.find(' ');
    if (pos != std::string::npos)
        arg = arg.substr(0, pos);
    
    std::string channelName = arg;
    Channel *channel;

    if (server.channelExists(channelName))
    {
        channel = server.getChannel(channelName);
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
        channel->addMember(&client);
        client.setChannelStatus(channel->getName(), MEMBER_STATUS); // par defaut, a le statut de membre
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
