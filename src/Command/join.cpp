#include "../../include/Command.hpp"

/*
**The JOIN command is used by client to start listening a specific
   channel
*/

void Command::join(std::vector<std::string> parsing, Client &client, Server &server)
{
    std::string channelName;
    std::string key;
    Channel *channel;

    if (parsing.size() < 2)
    {
        printError(ERR_NEEDMOREPARAMS(parsing.front()));
		server.sendToClient(&client, ERR_NEEDMOREPARAMS(parsing.front()));
        return ;
    }
    if (!client.isRegistered())
    {
        printError(ERR_NOTREGISTRED);
        server.sendToClient(&client, ERR_NOTREGISTRED);
        return ;
    }

    channelName = parsing[1];
    if (parsing.size() >= 3)
        key = parsing[2];

    if (!isValidChannelName(channelName))
    {
        printError(ERR_BADCHANNAME(channelName));
        server.sendToClient(&client, ERR_BADCHANNAME(channelName));
        return ;
    }

    channel = server.getChannel(channelName);
    if (channel)
    {
        if (channel->hasMember(&client))
            return ;
        if (channel->isInviteOnly() && !channel->isInvited(&client))
        {
            printError(ERR_INVITEONLYCHAN(channelName));
            server.sendToClient(&client, ERR_INVITEONLYCHAN(channelName));
            return ;
        }
        if (channel->isFull())
        {
            printError(ERR_CHANNELISFULL(channelName));
            server.sendToClient(&client, ERR_CHANNELISFULL(channelName));
            return ;
        }
        if (!channel->checkKey(key))
        {
            printError(ERR_BADCHANNELKEY(channelName));
            server.sendToClient(&client, ERR_BADCHANNELKEY(channelName));
            return ;
        }
    }

    server.joinClientToChannel(&client, channelName);

    channel = server.getChannel(channelName);
    if (channel)
    {
        if (channel->isInvited(&client))
            channel->removeInvite(&client);
    }
}
