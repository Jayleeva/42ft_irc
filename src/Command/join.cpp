#include "../../include/Command.hpp"

/*
**The JOIN command is used by client to start listening a specific
   channel
*/

void Command::join(Message const &msg, Client &client, Server &server)
{
	std::string arg = getArgument(msg.getMsg());
    std::string channelName = getTarget(arg);

    if (isEmptyArg(channelName))
    {
        printError(ERR_NEEDMOREPARAMS);
        return ;
    }
    if (!client.isRegistered())
    {
        printError(ERR_NOTREGISTERED);
        return ;
    }
    
    if (!isValidChannelName(channelName))
    {
        printError(ERR_BADCHANNELNAME);
        return ;
    }

    Channel *channel = server.getChannel(channelName);
    
    if (channel)
    {
        if (channel->hasMember(&client))
            return;
            
        if (channel->isInviteOnly() && !channel->isInvited(&client))
        {
            printError(ERR_INVITEONLYCHAN);
            return;
        }
    }
    else
        channel = server.createChannel(channelName);

    server.joinClientToChannel(&client, channelName);

    channel = server.getChannel(channelName);
    if (channel)
        channel->removeInvited(&client);
}
