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
				int j = 1;
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
							server.sendNewParams(*chan, &client, (flag[i] == '+' ? "+i" : "-i"), "");
							break;
						}
						case 't':
						{
							chan->setTopicRestricted((flag[i] == '+' ? true : false));
							server.sendNewParams(*chan, &client, (flag[i] == '+' ? "+t" : "-t"), "");
							break;
						}
						case 'k':
						{
							if (flag[i] == '-')
							{
								chan->removeKey();
								server.sendNewParams(*chan, &client, "-k", "");
							}
							else
							{
								std::vector<std::string>::iterator tmpit = it ++;
								tmpit ++;
								if (tmpit == parsing.end())
								{
									printError(ERR_NEEDMOREPARAMS(parsing.front()));
									server.sendToClient(&client, ERR_NEEDMOREPARAMS(parsing.front()));
									return;
								}
								std::string key = *tmpit;
								chan->setKey(key);
								server.sendNewParams(*chan, &client, "+k", key);
							}							
							break;
						}
						case 'l':
						{
							if (flag[i] == '-')
							{
								chan->removeUserLimit();
								server.sendNewParams(*chan, &client, "-l", "0");
							}
							else
							{
								std::vector<std::string>::iterator tmpit = it ++;
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
									printError(ERR_UNKNOWNMODE(*tmpit));
									server.sendToClient(&client, ERR_UNKNOWNMODE(*tmpit));
									return;
								}
								if (limit < 0)
								{
									printError(ERR_UNKNOWNMODE(*tmpit));
									server.sendToClient(&client, ERR_UNKNOWNMODE(*tmpit));
									return;
								}
								chan->setUserLimit(limit);
								server.sendNewParams(*chan, &client, "+l", *tmpit);
							}
							break;
						}
						case 'o':
						{
							std::vector<std::string>::iterator tmpit = it ++;
							tmpit ++;
							if (tmpit == parsing.end())
							{
								printError(ERR_NEEDMOREPARAMS(parsing.front()));
								server.sendToClient(&client, ERR_NEEDMOREPARAMS(parsing.front()));
								return;
							}
							std::string targetName = *tmpit;
							Client *target = server.getClientByNick(targetName);
							if (flag[i] == '-')
							{
								if (chan->isOperator(target))
								{
									chan->removeOperator(target);
									server.sendNewParams(*chan, &client, "-o", targetName);
								}
							}
							else
							{
								if (!chan->isOperator(target))
								{
									chan->addOperator(target);
									server.sendNewParams(*chan, &client, "+o", targetName);
								}
							}
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
}