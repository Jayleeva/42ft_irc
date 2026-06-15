#include "../include/Bot.hpp"
#include "../include/utils.hpp"
#include <cstdlib>

void Bot::handleMessage(Server &server, Channel *channel, const std::string &channelName, const std::string &message)
{
	int			dice;
	std::string	result;

	if (message.find("!help") != std::string::npos)
	{
		server.sendToChannel(*channel,
			NULL,
			RPL_PRIVMSG(std::string("Bot!bot@localhost"),
				channelName,
				":Commands: !help !dice !coinflip"));
	}

	if (message.find("!dice") != std::string::npos)
	{
		dice = rand() % 6 + 1;

		result = ":";
		result += ft_itoa(dice);

		server.sendToChannel(*channel,
			NULL,
			RPL_PRIVMSG(std::string("Bot!bot@localhost"),
				channelName,
				result));
	}

	if (message.find("!coinflip") != std::string::npos)
	{
		if (rand() % 2 == 0)
		{
			server.sendToChannel(*channel,
				NULL,
				RPL_PRIVMSG(std::string("Bot!bot@localhost"),
					channelName,
					":Heads"));
		}
		else
		{
			server.sendToChannel(*channel,
				NULL,
				RPL_PRIVMSG(std::string("Bot!bot@localhost"),
					channelName,
					":Tails"));
		}
	}
}