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

    std::string key = "";
    if  (parsing.size() >= 2)
        key = *(parsing.begin() + 2);
  
    server.joinClientToChannel(&client, channelName, key);
}
