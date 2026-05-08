#include "../../include/Command.hpp"

/*
** The PART message causes the client sending the message to be removed
   from the list of active users for all given channels listed in the
   parameter string.
*/

void Command::part(std::vector<std::string> parsing, Client &client, Server &server)
{
    if (parsing.size() < 2)
    {
        printError(ERR_NEEDMOREPARAMS);
        server.sendError(client, 461, ERR_NEEDMOREPARAMS);
        return ;
    }

    std::string channelName = *(parsing.begin() + 1);

    //vérifier si channel existe et si le client est membre du channel
    
    server.removeClientFromChannel(&client, channelName);
}