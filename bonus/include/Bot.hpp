#ifndef BOT_HPP
#define BOT_HPP

#include "Server.hpp"
#include "Channel.hpp"

class Bot
{
	public:
		static void handleMessage(Server &server,
			Channel *channel,
			const std::string &channelName,
			const std::string &message);
};

#endif