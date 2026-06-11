#include "../../include/Command.hpp"

void Command::user(std::vector<std::string> parsing, Client &client, Server &server)
{
    if (parsing.size() < 2)
    {
        printError(ERR_NEEDMOREPARAMS(parsing.front()));
		server.sendToClient(&client, ERR_NEEDMOREPARAMS(parsing.front()));
        return ;
    }

    if (!client.hasPass())
        return ;

    std::string arg = *(parsing.begin() + 1);
    client.setUsername(arg);
}
