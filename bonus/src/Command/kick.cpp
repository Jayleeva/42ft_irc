#include "../../include/Command.hpp"

void Command::kick(std::vector<std::string> parsing, Client &client, Server &server)
{
	std::vector<std::string>::iterator it = parsing.begin();

    if (parsing.size() < 3)
    {
        printError(ERR_NEEDMOREPARAMS(parsing.front()));
		server.sendToClient(&client, ERR_NEEDMOREPARAMS(parsing.front()));
        return ;
    }
  	std::string channelName = *(++it);
	std::string nickname = *(++it);
	std::string reason;

    std::cout << "target = " << *(it) << std::endl;
    std::string target = *it; // peut y en avoir plusieurs, faire un getline avec ',' en separateur
    std::vector<std::string> allTargets = getAllTargets(*it);
    it += allTargets.size() -1; // incrementer du nombre de targets
	if (it == parsing.end())
		reason = "Kicked";
	else
    	reason = rebuildMessage(it, parsing.end());		

	if (!server.channelExists(channelName))
	{
    	printError(ERR_NOSUCHCHANNEL(channelName));
		server.sendToClient(&client, ERR_NOSUCHCHANNEL(channelName));
		return;
	}

	Channel *channel = server.getChannel(channelName);

    if (!channel->isOperator(&client))
    {		
		printError(ERR_CHANOPRIVSNEEDED(channelName));
		server.sendToClient(&client, ERR_CHANOPRIVSNEEDED(channelName));
		return;
    }

	for (std::vector<std::string>::iterator it1 = allTargets.begin(); it1 != allTargets.end(); it1 ++) // pour envoyer a toutes les targets
    {
		Client *targetClient = server.getClientByNick(*(it1));

		if(!targetClient)
		{
			printError(ERR_NOSUCHNICK(nickname));
			server.sendToClient(&client, ERR_NOSUCHNICK(nickname));
			return;
		}

		if (!channel->hasMember(targetClient))
		{
			printError(ERR_NOTONCHANNEL(channelName));
			server.sendToClient(&client, ERR_NOTONCHANNEL(channelName));
			return;
		}

		server.sendKickConfirmation(&client, targetClient, channel, reason);
		server.removeClientFromChannel(targetClient, channel, false);
	}
}