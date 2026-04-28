#include "../../include/Command.hpp"

/*
**This command allows to choose a client nickname.
**The server must:
    check that the nickname is not empty
    check if there is no invalid char
    check that it is not already taken by another client
    save this nickname in the `Client` object
*/

void Command::nick(Message const &msg, Client &client, Server &server)
{
    std::string arg = getArgument(msg.getMsg());
    std::string nickname = getTarget(arg);

    if (isEmptyArg(nickname))
    {
        printError(ERR_NEEDMOREPARAMS);
        return ;
    }

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
