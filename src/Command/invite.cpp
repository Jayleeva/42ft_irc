#include "../../include/Command.hpp"

/*
**This function allows a cllient to invite another client into a channel
** The command does :
			Retrieve the arguments
			Extract nickname and channel
			Verify that channel et nickname exists
			Send an invitation
*/
// void Command::invite(Message const &msg, Client &client, Server &server)
// {    
// 	std::string arg = getArgument(msg.getMsg());

//     size_t i = 0;
//     while (i < arg.size() && arg[i] == ' ')
//         i++;
//     arg = arg.substr(i);

//     if (isEmptyArg(arg))
//     {
//         printError(ERR_NEEDMOREPARAMS);
//         return ;
//     }

// 	size_t pos = arg.find(' ');
// 	if (pos == std::string::npos)
// 	{
// 		printError(ERR_NEEDMOREPARAMS);
// 		return ;
// 	}

// 	std::string nickname = arg.substr(0, pos);
// 	std::string channelName = arg.substr(pos + 1);

// 	i = 0;
// 	while (i < channelName.size() && channelName[i] == ' ')
// 		i++;
// 	channelName = channelName.substr(i);
// }

// A finir plus tard