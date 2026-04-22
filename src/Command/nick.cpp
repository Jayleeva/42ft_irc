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

    size_t i = 0;
    while (i < arg.size() && arg[i] == ' ')
        i++;
    arg = arg.substr(i);

    if (isEmptyArg(arg))
    {
        printError(ERR_NEEDMOREPARAMS);
        return ;
    }

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
}

/*
**bool nicknameExists(std::string nick) : à faire dans server ou ici ?
*/