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

    for (std::vector<std::string>::iterator its = it; its != ite; its ++)
    {
        res.append(*its);
    }
    return (res);
}


std::vector<std::string> getAllTargets(std::string list)
{
    std::vector<std::string>    res;

	std::string			        element;
    std::stringstream 	        ss(list);

	while (getline(ss, element, ','))
		res.push_back(element);
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
    std::vector<std::string> allTargets = getAllTargets(*it);
    it += allTargets.size(); // incrementer du nombre de targets
    std::string message = rebuildMessage(it, parsing.end()); 

    for (std::vector<std::string>::iterator it1 = allTargets.begin(); it1 != allTargets.end(); it1 ++) // pour envoyer a toutes les targets
    {
        //channel
        if (*(it1)->begin() == '#')
        {
            Channel *channel = server.getChannel(*it1);
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
            server.sendMessageToChannel(&client, channel, message); // NOTE
        }

        //user
        else
        {
            Client *targetClient = server.getClientByNick(*(it1));
            if (!targetClient)
            {
                printError(ERR_NOSUCHNICK);
                return ;
            }
            server.sendMessageToClient(&client, targetClient, message); // NOTE: *targetClient
        }
    }
}
