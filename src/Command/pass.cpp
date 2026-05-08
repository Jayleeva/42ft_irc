#include "../../include/Command.hpp"

/*
**The PASS command is used to set a 'connection password'.
** PASS <password>   
*/

void Command::pass(std::vector<std::string> parsing, Client &client, Server &server)
{
    if (parsing.size() < 2)
    {
        printError(ERR_NEEDMOREPARAMS);
        server.sendError(client, "461", ERR_NEEDMOREPARAMS);
        return ;
    }

    if (client.isRegistered())
    {
        printError(ERR_ALREADYREGISTRED);
        server.sendError(client, "462", ERR_ALREADYREGISTRED);
        return;
    }

    std::string arg = *(parsing.begin() + 1);
    arg = arg.substr(0, arg.find("\r\n"));
    std::cout << "password = '" << arg << "'" << std::endl;

    if (arg != server.getPassword())
    {
        printError(ERR_PASSWDMISMATCH);
        std::string nickname = client.getNickname();
        if (nickname.empty())
            nickname = "<unknownclient>";
        std::string mismatch = " " + nickname + ERR_PASSWDMISMATCH;
        server.sendError(client, "464", mismatch.c_str());
        return ;
    }
    client.setPassValid();
}