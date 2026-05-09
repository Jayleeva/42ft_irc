#include "../../include/Command.hpp"

/*
**The PASS command is used to set a 'connection password'.
** PASS <password>   
*/

void Command::pass(std::vector<std::string> parsing, Client &client, Server &server)
{
    if (parsing.size() < 2)
    {
        printError(ERR_NEEDMOREPARAMS(parsing.front()));
		server.sendToClient(&client, ERR_NEEDMOREPARAMS(parsing.front()));
        return ;
    }

    if (client.isRegistered())
    {
        printError(ERR_ALREADYREGISTRED);
        server.sendToClient(&client, ERR_ALREADYREGISTRED);
        return;
    }

    std::string arg = *(parsing.begin() + 1);
    arg = arg.substr(0, arg.find("\r\n"));
    std::cout << "password = '" << arg << "'" << std::endl;

    if (arg != server.getPassword())
    {
        std::string nickname = client.getNickname();
        if (nickname.empty())
            nickname = "noNickname"; // get hostname de la machine?
        printError(ERR_PASSWDMISMATCH(nickname));
        server.sendToClient(&client, ERR_PASSWDMISMATCH(nickname));
        return ;
    }
    client.setPassValid();
}