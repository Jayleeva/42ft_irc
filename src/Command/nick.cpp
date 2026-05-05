#include "../../include/Command.hpp"

/*
**NICK message is used to give user a nickname or change the previous one.
**NICK <nickname>
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
