#include "../../include/Command.hpp"
#include "../../include/Bot.hpp"

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
        if (its + 1 != ite)
            res.append(" ");
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
        printError(ERR_NEEDMOREPARAMS(parsing.front()));
		server.sendToClient(&client, ERR_NEEDMOREPARAMS(parsing.front()));
        return ;
    }
    if (parsing.size() < 3)
    {
        printError(ERR_NOTEXTTOSEND);
        server.sendToClient(&client, ERR_NOTEXTTOSEND);
        return ;
    }
    std::vector<std::string>::iterator it = parsing.begin() + 1;

    std::cout << "target = " << *(it) << std::endl;
    std::string target = *it; // peut y en avoir plusieurs, faire un getline avec ',' en separateur
    std::vector<std::string> allTargets = getAllTargets(*it);
    it += allTargets.size(); // incrementer du nombre de targets
    std::string message = rebuildMessage(it, parsing.end());
    std::cout << "message = '" << message << "'" << std::endl;

    for (std::vector<std::string>::iterator it1 = allTargets.begin(); it1 != allTargets.end(); it1 ++) // pour envoyer a toutes les targets
    {
        //channel
        if (*(it1)->begin() == '#')
        {
            Channel *channel = server.getChannel(*it1);
            if (!channel)
            {
                printError(ERR_NOSUCHCHANNEL(channel->getName()));
                server.sendToClient(&client, ERR_NOSUCHCHANNEL(channel->getName()));
                return ;
            }
            if (!channel->hasMember(&client))
            {   
                printError(ERR_CANNOTSENDTOCHAN(channel->getName()));
                server.sendToClient(&client, ERR_CANNOTSENDTOCHAN(channel->getName()));
                return ;
            }
            server.sendMessageToChannel(&client, *channel, message);
            Bot::handleMessage(server, channel, *it1, message);
        }

        //user
        else
        {
            Client *targetClient = server.getClientByNick(*(it1));
            if (!targetClient)
            {
                printError(ERR_NOSUCHNICK(target));
                server.sendToClient(&client, ERR_NOSUCHNICK(target));
                return ;
            }
            server.sendToClient(targetClient, RPL_PRIVMSG(client.getNickname(), targetClient->getNickname(), message));
        }
    }
}