#include "../../include/Command.hpp"

/*
**The JOIN command is used by client to start listening a specific
   channel
*/

void Command::join(Message const &msg, Client &client, Server &server)
{
	std::string arg = getArgument(msg.getMsg());
    std::string channel = getTarget(arg);

    if (isEmptyArg(channel))
    {
        printError(ERR_NEEDMOREPARAMS);
        return ;
    }
    if (!client.isRegistered())
    {
        printError(ERR_NOTREGISTERED);
        return ;
    }
    
    if (!isValidChannelName(channel))
    {
        printError(ERR_BADCHANNELNAME);
        return ;
    }
    server.joinClientToChannel(&client, channel);
}

    /*std::string channelName = arg;
    Channel *channel;

    if (server.channelExists(channelName))
        channel = server.getChannel(channelName);
    else
        channel = server.createChannel(channelName);
    
    channel->addMember(&client);*/