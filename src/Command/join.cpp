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

    if (!client.isRegistered())
    {
        printError(ERR_NOTREGISTRED);
        return ;
    }
    
    if (!isValidChannelName(channelName))
    {
        printError(ERR_BADCHANNELNAME);
        return ;
    }

    Channel *channel = server.getChannel(channelName);
    
    /*if (channel)
    {
        if (channel->hasMember(&client))
            return;
            
        if (channel->isInviteOnly() && !channel->isInvited(&client))
        {
            printError(ERR_INVITEONLYCHAN);
            return;
        }
    }*/

    server.joinClientToChannel(&client, channelName);

    channel = server.getChannel(channelName);
    if (channel)
        channel->removeInvite(&client);
}
