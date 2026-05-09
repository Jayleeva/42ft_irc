#ifndef UTILS_HPP
# define UTILS_HPP

#include <iostream>
#include <string>
#include "Client.hpp"
#include "Channel.hpp"
#include "Server.hpp"

class Client;
class Channel;
class Command;

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
#define ERR_NOTREGISTRED "451 :You have not registered" 
#define ERR_ALREADYREGISTRED "462 :You may not reregister" 
#define ERR_PASSWDMISMATCH(nick) "464 " + nick + ":Password incorrect" // besoin du nick?

#define ERR_ERRONEUSNICKNAME "432 <nick> :Erroneus nickname"
#define ERR_NICKNAMEINUSE "433 <nick> :Nickname is already used" 

#define ERR_UNKNOWNCOMMAND "421 <command> :Unknown command"
#define ERR_NEEDMOREPARAMS "461 <command> :Not enough parameters" 
#define ERR_NONICKNAMEGIVEN "431 :No nickname given"
//#define ERR_UMODEUNKNOWNFLAG "501 :Unknown USERMODE flag"
#define ERR_UNKNOWNMODE "472 <char> :is unknown mode char to me"

#define ERR_BADCHANNAME "479 <channel> :Bad channel name" // sans argument?

#define ERR_NOSUCHCHANNEL "403 <channel> :No such channel"
#define ERR_NOTONCHANNEL "442 <channel> :You're not on that channel"
#define ERR_CHANNELISFULL "471 <channel> :Cannot join channel (+l)"
#define ERR_BADCHANNELKEY "475 <channel> :Cannot join channel (+k)"
#define ERR_INVITEONLYCHAN "473 <channel> :Cannot join channel (+i)"
//#define ERR_BANNEDFROMCHAN " :Cannot join channel (+b)"
#define ERR_TOOMANYCHANNELS "405 <channel> :You have joined too many channels"

#define ERR_CHANOPRIVSNEEDED "482 <channel> :You're not channel operator"

#define ERR_NOSUCHNICK "401 <nick> :No such nick"
#define ERR_USERNOTINCHANNEL "441 <nick> <channel> :They aren't on that channel"
#define ERR_USERONCHANNEL "443 <nick> <channel> :is already on channel"

#define ERR_NOTEXTTOSEND "412 :No text to send"
#define ERR_CANNOTSENDTOCHAN "404 <channel> :Cannot send to channel"

//Return messages
#define RPL_WELCOME "001 :Welcome to the ircserv network <nickname>" // to confirm connection
#define RPL_NAMREPLY "353 <channel> :['@'/'+']<nick> (['@'/'+']<nick>)*" //to confirm join
#define RPL_ENDOFNAMES "366 <channel> :End of /NAMES list"  // to close the list of names
#define RPL_NOTOPIC "331 <channel> :No topic is set" // to confirm there's no topic
#define RPL_TOPIC "332 <channel> :<topic>" // to confirm topic
#define RPL_INVITING "341 <nick> <channel>" // to confirm the invitation
#define RPL_CHANNELMODEIS "324 <channel> <mode> <mode params>" // to confirm mode

//parsing functions
std::string     getCommand(const std::string& msg);

//Utils functions
void            printError(const std::string& errorMsg);
bool            channelExists(std::map<std::string, Channel*> channels, std::string name);
bool 			isValidChannelName(const std::string &name);
Command parseCmd(std::string input);
//std::string     ft_itoa(int i);
#endif