#include "../../include/Command.hpp"

/*
** PRIVMSG is used to send private messages between users.  <receiver>
   is the nickname of the receiver of the message.  <receiver> can also
   be a list of names or channels separated with commas.
   Parameters: <receiver>{,<receiver>} <text to be sent>
*/

void Command::privmsg(Message const &msg, Client &client, Server &server)
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

    size_t pos = arg.find(' ');
    if (pos != std::string::npos)
    {
        printError(ERR_NEEDMOREPARAMS);
        return ;
    }
    
    std::string target = arg.substr(0, pos);
    std::string message = arg.substr(pos + 1);

    //message
    i = 0;
    while (i < message.size() && message[i] == ' ')
        i++;
    message = message.substr(i);

    if (message.empty())
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
        Client *targetClient = server.getClientByNick(target); //fonction à créer
        if (!targetClient)
        {
            printError(ERR_NOSUCHNICK);
            return ;
        }

        server.sendMessageToClient(*targetClient, message); //fonction à créer
    }
}
