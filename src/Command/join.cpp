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
    if (!client.isRegistered())
    {
        printError(ERR_NOTREGISTERED);
        return ;
    }

    size_t pos = arg.find(' ');
    if (pos != std::string::npos)
        arg = arg.substr(0, pos);
    
    /*std::string channelName = arg;
    Channel *channel;

    if (server.channelExists(channelName))
        channel = server.getChannel(channelName);
    else
        channel = server.createChannel(channelName);
    
    channel->addMember(&client);*/
    if (!isValidChannelName(arg))
    {
        printError(ERR_BADCHANNELNAME);
        return ;
    }
    server.joinClientToChannel(&client, arg);
}

/*
Server - Channels :

- bool channelExists
- getChannel
- createChannel
- joinClientToChannel
- removeClientFromChannelgetPassword()
*/