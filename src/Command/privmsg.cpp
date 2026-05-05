#include "../../include/Command.hpp"

/*
** PRIVMSG is used to send private messages between users.  <receiver>
   is the nickname of the receiver of the message.  <receiver> can also
   be a list of names or channels separated with commas.
**PRIVMSG <receiver>{,<receiver>} <text to be sent>
*/

std::string    rebuildMessage(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite)
{
    std::string res = "";

    for (it; it != ite; it ++)
    {
        res.append(*it);
    }
    return (res);
}

void Command::privmsg(std::vector<std::string> parsing, Client &client, Server &server)
{
    if (parsing.size() < 2)
    {
        printError(ERR_NEEDMOREPARAMS);
        return ;
    }
    if (parsing.size() < 3)
    {
        printError(ERR_NOTEXTTOSEND);
        return ;
    }
    std::vector<std::string>::iterator it = parsing.begin() + 1;

    std::string target = *it; // peut y en avoir plusieurs, faire un getline avec ',' en separateur
    it ++; // incrementer du nombre de target
    std::string message = rebuildMessage(it, parsing.end()); 

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

        server.sendMessageToClient(targetClient, message); // NOTE: *targetClient
    }
}
