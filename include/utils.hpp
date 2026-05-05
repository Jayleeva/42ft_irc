#ifndef UTILS_HPP
# define UTILS_HPP

#include <iostream>
#include <string>
#include "Client.hpp"
#include "Channel.hpp"

class Client;
class Channel;

//Colors
# define DEFAULT "\001\033[0;39m\002"
# define YELLOW "\001\033[1;93m\002"
# define RED "\001\033[0;31m\002"
# define GREEN "\001\033[1;32m\002"
# define MAG  "\001\033[1;35m\002"

//Colors
# define DEFAULT "\001\033[0;39m\002"
# define YELLOW "\001\033[1;93m\002"
# define RED "\001\033[0;31m\002"
# define GREEN "\001\033[1;32m\002"
# define MAG  "\001\033[1;35m\002"

//Error messages
#define ERR_NOTREGISTRED " :You have not registered"
#define ERR_ALREADYREGISTRED " :You may not reregister"
#define ERR_PASSWDMISMATCH " :Password incorrect"

#define ERR_ERRONEUSNICKNAME " :Erroneus nickname"
#define ERR_NICKNAMEINUSE " :Nickname is already used"

#define ERR_UNKNOWNCOMMAND " :Unknown command"
#define ERR_NEEDMOREPARAMS " :Not enough parameters"
#define ERR_NONICKNAMEGIVEN " :No nickname given"
#define ERR_UMODEUNKNOWNFLAG " :Unknown MODE flag"
#define ERR_UNKNOWNMODE " :is unknown mode char to me"

#define ERR_BADCHANNELNAME " : Bad channel name"

#define ERR_NOTONCHANNEL " :You're not on that channel"
#define ERR_NOSUCHCHANNEL " :No such channel"
#define ERR_CHANNELISFULL " :Cannot join channel (+l)"
#define ERR_BADCHANNELKEY " :Cannot join channel (+k)"
#define ERR_INVITEONLYCHAN " :Cannot join channel (+i)"
#define ERR_BANNEDFROMCHAN " :Cannot join channel (+b)"
#define ERR_TOOMANYCHANNELS " :You have joined too many channels"

#define ERR_CHANOPRIVSNEEDED " :You're not channel operator"
#define ERR_NOPRIVILEGES " :Permission Denied- You're not an IRC operator"

#define ERR_NOSUCHNICK " :No such nick/channel"
#define ERR_USERNOTINCHANNEL " :They aren't on that channel"
#define ERR_USERONCHANNEL " :is already on channel"

//Return messages
#define RPL_WELCOME ":ircserv 001 " // to confirm connection

#define RPL_NAMREPLY "[@|+]" //to confirm join // <channel> :[[@|+]<nick> [[@|+]<nick> [...]]]
#define RPL_ENDOFNAMES " :End of /NAMES list"  // to close the list of names
#define RPL_NOTOPIC " :No topic is set" // to confirm there's no topic
#define RPL_TOPIC "<channel> :<topic>" // to confirm topic
#define RPL_INVITING "<channel> <nick>" // to confirm the invitation
#define RPL_CHANNELMODEIS "<channel> <mode> <mode params>" // to confirm mode
//#define PART  to confirm part ?
//#define KICK  to confirm kick ?

//parsing functions
std::string     getCommand(const std::string& msg);

//Utils functions
bool            isEmptyArg(const std::string &arg);
std::string     getArgument(const std::string& msg);
void            printError(const std::string& errorMsg);
int             findClientByName(std::map<int, Client*> _clients, std::string name);
bool            channelExists(std::map<std::string, Channel*> channels, std::string name);
bool 			isValidChannelName(const std::string &name);
#endif