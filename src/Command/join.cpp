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
        printError(ERR_NEEDMOREPARAMS);
        server.sendError(client, 461, ERR_NEEDMOREPARAMS);
        return ;
    }
    if (!client.isRegistered())
    {
        printError(ERR_NOTREGISTRED);
        server.sendError(client, 451, ERR_NOTREGISTRED);
        return ;
    }

    channelName = parsing[1];
    if (parsing.size() >= 3)
        key = parsing[2];

    if (!isValidChannelName(channelName))
    {
        printError(ERR_BADCHANNAME);
        server.sendError(client, 479, ERR_BADCHANNAME);
        return ;
    }

    channel = server.getChannel(channelName);
    if (channel)
    {
        if (channel->hasMember(&client))
            return ;
        if (channel->isInviteOnly() && !channel->isInvited(&client))
        {
            printError(ERR_INVITEONLYCHAN);
            server.sendError(client, 473, ERR_INVITEONLYCHAN);
            return ;
        }
        if (channel->isFull())
        {
            printError(ERR_CHANNELISFULL);
            server.sendError(client, 471, ERR_CHANNELISFULL);
            return ;
        }
        if (!channel->checkKey(key))
        {
            printError(ERR_BADCHANNELKEY);
            server.sendError(client, 475, ERR_BADCHANNELKEY);
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
