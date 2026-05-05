#include "../../include/Command.hpp"

/*
** PRIVMSG is used to send private messages between users.  <receiver>
   is the nickname of the receiver of the message.  <receiver> can also
   be a list of names or channels separated with commas.
**PRIVMSG <receiver>{,<receiver>} <text to be sent>
*/

void Command::privmsg(Message const &msg, Client &client, Server &server)
{
    std::string arg = getArgument(msg.getMsg());

    if (isEmptyArg(arg))
    {
        printError(ERR_NEEDMOREPARAMS);
        return ;
    }

    std::string target = getTarget(arg);
    std::string message = getMessage(arg);

    //message
    if (isEmptyArg(message))
    {
        printError(ERR_NOTEXTTOSEND);
        return ;
    }

    //channel
    if (target[0] == '#')
    {
        Channel *channel = server.getChannel(target);
        if (!channel)  
        {
            printError(ERR_NOSUCHCHANNEL);
            return ;
        }
        if (!channel->hasMember(&client))
        {   
            printError(ERR_CANNOTSENDTOCHAN);
            return ;
        }
        //fonction pour envoyer message à tous les membres du channel
        //sauf le sender à créer dans Server
    }

    //user
    else
    {
        Client *targetClient = server.getClientByNick(target);
        if (!targetClient)
        {
            printError(ERR_NOSUCHNICK);
            return ;
        }

        server.sendMessageToClient(*targetClient, message);
    }
}
