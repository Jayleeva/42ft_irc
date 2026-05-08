#include "../../include/Command.hpp"

/*
** The USER message is used at the beginning of connection to specify
   the username, hostname, servername and realname of the new user
**USER <username> <hostname> <servername> <realname>
*/

void Command::user(std::vector<std::string> parsing, Client &client, Server &server)
{
    if (parsing.size() < 2)
    {
        printError(ERR_NEEDMOREPARAMS);
        server.sendError(client, "461", ERR_NEEDMOREPARAMS);
        return ;
    }

    if (!client.hasPass())
    {
        /*std::string nickname = client.getNickname();
        if (nickname.empty())
            nickname = "<unknownclient>";
        std::string mismatch = " " + nickname + ERR_PASSWDMISMATCH;
        server.sendError(client, "464", mismatch.c_str());*/
        return ;
    }

    std::string arg = *(parsing.begin() + 1);
    client.setUsername(arg);
}
