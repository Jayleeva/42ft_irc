#include "../include/Command.hpp"

/*
**This command allows to choose a client nickname.
**The server must:
    check that the nickname is not empty
    check if there is no spaces
    check that it is not already taken by another client
    save this nickname in the `Client` object
*/

void Command::nick(Message const &msg, Client &client, Server &server)
{
    std::string arg = getArgument(msg.getMsg());

    if (isEmptyArg(arg))
    {
        printError(ERR_NEEDMOREPARAMS);
        return ;
    }

    size_t i = 0;
    while (i < arg.size())
    {
        if (arg[i] == ' ')
        {
            printError(ERR_ERRONEUSNICKNAME);
            return ;
        }
        i++;
    }

    //check if nickname already exists
    if (server.nicknameExists(arg)) // fonction à créer
    {
        printError(ERR_NICKNAMEINUSE);
        return ;
    }
        
    client.setNickname(arg);
}

/*
**bool nicknameExists(std::string nick) : à faire dans server ou ici ?
*/