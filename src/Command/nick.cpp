#include "../../include/Command.hpp"

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
        printError(ERR_NEEDMOREPARAMS(parsing.front()));
		server.sendToClient(&client, ERR_NEEDMOREPARAMS(parsing.front()));
        return ;
    }

    std::string nickname = *(parsing.begin() + 1);

    if (!client.hasPass())
    {
        std::cout << "hello\n";
        return ;
    } 

    for (size_t j = 0; j < nickname.size(); j++)
    {
        if (nickname[j] == ' ' || nickname[j] == '\t')
        {
            printError(ERR_ERRONEUSNICKNAME(nickname));
            server.sendToClient(&client, ERR_ERRONEUSNICKNAME(nickname));
            return ;
        }
    }

    if (nickname[0] == '#' || nickname[0] == '&')
    {
        printError(ERR_ERRONEUSNICKNAME(nickname));
        server.sendToClient(&client, ERR_ERRONEUSNICKNAME(nickname));
        return;
    }

    if (server.nicknameExists(nickname) && nickname != client.getNickname())
    {
        client.setNeedRename(true);
        printError(ERR_NICKNAMEINUSE(nickname));
        server.sendToClient(&client, ERR_NICKNAMEINUSE(nickname));
        return ;
    }

    bool overwrite = false;
    std::string oldnick = client.getNickname();
    if (client.hasNick())
        overwrite = true;

    client.setNickname(nickname);

    if (client.getNeedRename() == true)
    {
        client.setNeedRename(false);
        client.tryRegister();
        server.sendToClient(&client, RPL_WELCOME(nickname));
    }

    if (overwrite)
    {
        server.sendToClient(&client, RPL_NICK(oldnick, nickname));
        server.sendToClient(&client, RPL_WELCOME(nickname));
    }
}