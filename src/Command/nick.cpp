#include "../../include/Command.hpp"

/*
**NICK message is used to give user a nickname or change the previous one.
**NICK <nickname>
*/

void   printCurrentNicknames(Server &server)
{
    std::cout << "Current nicknames:\n";
    std::map<int, Client*> map = server.getMapClients();
    for (std::map<int, Client*>::iterator it = map.begin(); it != map.end(); it ++)
        std::cout << "- " << it->second->getNickname() << std::endl; 
}

void Command::nick(std::vector<std::string> parsing, Client &client, Server &server)
{
    if (parsing.size() < 2)
    {
        printError(ERR_NEEDMOREPARAMS);
        return ;
    }

    if (!client.hasPass())
    {
        printError(ERR_PASSWDMISMATCH);
        return ;
    }

    std::string nickname = *(parsing.begin() + 1);

    for (size_t j = 0; j < nickname.size(); j++)
    {
        if (nickname[j] == ' ' || nickname[j] == '\t')
        {
            printError(ERR_ERRONEUSNICKNAME);
            return ;
        }
    }

    if (nickname[0] == '#' || nickname[0] == '&')
    {
        printError(ERR_ERRONEUSNICKNAME);
        return;
    }

    if (server.nicknameExists(nickname) && nickname != client.getNickname())
    {
        printError(ERR_NICKNAMEINUSE);
        return ;
    }

    client.setNickname(nickname);
}
