#include "../../include/Command.hpp"

void Command::mode(std::vector<std::string> parsing, Client &client, Server &server)
{
	std::vector<std::string>::iterator it = parsing.begin();
	ssize_t	size = parsing.size();

	if (size < 2)
	{
        printError(ERR_NEEDMOREPARAMS(parsing.front()));
		server.sendToClient(&client, ERR_NEEDMOREPARAMS(parsing.front()));
		return;
	}
	it ++;
	std::string channelName = *it;
    if (server.channelExists(channelName) == false)
	{
    	printError(ERR_NOSUCHCHANNEL(channelName));
		server.sendToClient(&client, ERR_NOSUCHCHANNEL(channelName));
		return;
	}
	Channel *chan = server.getChannel(channelName);
	if (size == 2)
	{
		server.sendToClient(&client, RPL_CHANNELMODEIS(channelName, chan->getMode(), chan->getModeParams()));
		return;
	}

	if (chan->isOperator(&client) == false)
	{
		printError(ERR_CHANOPRIVSNEEDED(channelName));
		server.sendToClient(&client, ERR_CHANOPRIVSNEEDED(channelName));
		return;
	}
	it ++;
	
	while (it != parsing.end())
	{
		std::string flag = *it;
		int i = 0;
		while (flag[i])
		{
			if (flag[i] == '+' || flag[i] == '-')
			{
				int j = 0;
				while (flag[i + j])
				{
					if (!flag[i + j])
					{
						printError(ERR_UNKNOWNMODE(flag));
						server.sendToClient(&client, ERR_UNKNOWNMODE(flag));
						return;
					}
					switch (flag[i + j])
					{
						case 'i':
						{
							chan->setInviteOnly((flag[i] == '+' ? true : false));
							break;
						}
						case 't':
						{
							chan->setTopicRestricted((flag[i] == '+' ? true : false));
							break;
						}
						case 'k':
						{
							if (flag[i] == '-')
								chan->removeKey();
							else
							{
								std::vector<std::string>::iterator tmpit = it ++;
								if (tmpit == parsing.end())
								{
									printError(ERR_NEEDMOREPARAMS(parsing.front()));
									server.sendToClient(&client, ERR_NEEDMOREPARAMS(parsing.front()));
									return;
								}
								std::string key = *tmpit;
								chan->setKey(key);
							}							
							break;
						}
						case 'l':
						{
							if (flag[i] == '-')
								chan->removeUserLimit();
							else
							{
								std::vector<std::string>::iterator tmpit = it;
								tmpit ++;
								if (tmpit == parsing.end())
								{
									printError(ERR_NEEDMOREPARAMS(parsing.front()));
									server.sendToClient(&client, ERR_NEEDMOREPARAMS(parsing.front()));
									return;
								}
								int limit;
								try
								{
									limit = ft_stoi(*tmpit);
								}
								catch (std::exception &e)
								{
									std::cout << "tmpit KO = " << *tmpit << std::endl;
									printError(ERR_UNKNOWNMODE(*tmpit));
									server.sendToClient(&client, ERR_UNKNOWNMODE(*tmpit));
									return;
								}
								std::cout << "tmpit OK = " << *tmpit << std::endl;
								chan->setUserLimit(limit);
							}
							break;
						}
						case 'o':
						{
							std::vector<std::string>::iterator tmpit = it ++;
							if (tmpit == parsing.end())
							{
								printError(ERR_NEEDMOREPARAMS(parsing.front()));
								server.sendToClient(&client, ERR_NEEDMOREPARAMS(parsing.front()));
								return;
							}
							std::string targetName = *tmpit;
							Client *target = server.getClientByNick(targetName);
							if (chan->isOperator(target))
								chan->removeOperator(target);
							else
								chan->addOperator(target);
							break;
						}
						default:
						{
							printError(ERR_UNKNOWNMODE(flag));
							server.sendToClient(&client, ERR_UNKNOWNMODE(flag));
							return;
						}
						break;
					}
					j ++;
				}
			}
			i ++;
		}
		it ++;
	}
	server.sendNewParams(*chan, &client, chan->getMode(), chan->getModeParams());
}

/*
**i : Set/remove Invite-only channel
**t: Set/remove the restrictions of the TOPIC command to channel operators
**k: Set/remove the channel key (password)
**o: Give/take channel operator privilege
**l: Set/remove the user limit to channel
*/