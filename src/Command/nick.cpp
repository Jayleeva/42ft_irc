#include "../../include/Command.hpp"

/*
**This command allows to choose a client nickname.
**The server must:
    check that the nickname is not empty
    check if there is no invalid char
    check that it is not already taken by another client
    save this nickname in the `Client` object
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
    std::string arg = *(parsing.begin() + 1);

    for (size_t j = 0; j < arg.size(); j++)
    {
        if (arg[j] == ' ' || arg[j] == '\t')
        {
            printError(ERR_ERRONEUSNICKNAME);
            return ;
        }
    }

    if (arg[0] == '#' || arg[0] == '&')
    {
        printError(ERR_ERRONEUSNICKNAME);
        return;
    }

    if (server.nicknameExists(arg) && arg != client.getNickname())
    {
        printError(ERR_NICKNAMEINUSE);
        return ;
    }
        
    client.setNickname(arg);
    //printCurrentNicknames(server);
}

/*
**bool nicknameExists(std::string nick) : à faire dans server ou ici ?
*/