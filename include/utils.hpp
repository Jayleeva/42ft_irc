#ifndef UTILS_HPP
# define UTILS_HPP

#include <iostream>
#include <string>
#include <limits>
#include <signal.h>
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

//Max and min int
# define MAX_INT std::numeric_limits<int>::max()
# define MIN_INT std::numeric_limits<int>::min() 

//Error messages
#define ERR_NOTREGISTRED(nick) "451 " + nick + ":You have not registered" 
#define ERR_ALREADYREGISTRED "462 :You may not reregister" 
#define ERR_PASSWDMISMATCH(nick) ("464 " + nick + " :Password incorrect")

#define ERR_ERRONEUSNICKNAME(nick) ("432 " + nick + " :Erroneus nickname")
#define ERR_NICKNAMEINUSE(nick) ("433 " + nick + " :Nickname is already used")

#define ERR_UNKNOWNCOMMAND(command) ("421 " + command + " :Unknown command")
#define ERR_NEEDMOREPARAMS(command) ("461 " + command + " :Not enough parameters" )
#define ERR_NONICKNAMEGIVEN "431 :No nickname given"
#define ERR_UNKNOWNMODE(char) ("472 " + char + " :is unknown mode char to me")

#define ERR_BADCHANNAME(channel) ("479 " + channel + " :Bad channel name") // sans argument?

#define ERR_NOSUCHCHANNEL(channel) ("403 " + channel + " :No such channel")
#define ERR_NOTONCHANNEL(channel) ("442 " + channel + " :You're not on that channel")
#define ERR_CHANNELISFULL(channel) ("471 " + channel + " :Cannot join channel (+l)")
#define ERR_BADCHANNELKEY(channel) ("475 " + channel + " :Cannot join channel (+k)")
#define ERR_INVITEONLYCHAN(channel) ("473 " + channel + " :Cannot join channel (+i)")
//#define ERR_BANNEDFROMCHAN(channel) ("474 " + channel + " :Cannot join channel (+b)")
#define ERR_TOOMANYCHANNELS(channel) ("405 " + channel + " :You have joined too many channels")

#define ERR_CHANOPRIVSNEEDED(channel) ("482 " + channel + " :You're not channel operator")

#define ERR_NOSUCHNICK(nick) ("401 " + nick + " :No such nick")
#define ERR_USERNOTINCHANNEL(nick, channel) ("441 " + nick + " " + channel + " :They aren't on that channel")
#define ERR_USERONCHANNEL(nick, channel) ("443 " + nick + " " + channel + " :is already on channel")

#define ERR_NOTEXTTOSEND "412 :No text to send"
#define ERR_CANNOTSENDTOCHAN(channel) ("404 " + channel + " :Cannot send to channel")

//Return messages
#define RPL_WELCOME(nick)                               "001 " + nick + " :Welcome to the ircserv network " + nick + "!" // to confirm connection
#define RPL_NAMREPLY(nick, channel, list)               "353 " + nick + " " + channel + " " + list // ":['@'/'+']<nick> (['@'/'+']<nick>)*" //to confirm join
#define RPL_ENDOFNAMES(nick, channel)                   "366 " + nick + " " + channel + " :End of /NAMES list"  // to close the list of names
#define RPL_NOTOPIC(channel)                            "331 " + channel + " " + channel // to confirm there's no topic
#define RPL_TOPIC(channel, topic)                       "332 " + channel + " " + channel + " " + topic // to confirm topic
#define RPL_INVITING(nick, target, channel)             "341 " + nick + " " + target + " " + channel // to confirm the invitation
#define RPL_CHANNELMODEIS(channel, mode, params)        "324 " + channel + " "  + channel + " " + mode + " " + params // to confirm mode

#define RPL_CAP(nick)                                   "CAP * LS :" + nick
#define RPL_NICK(oldnick, newnick)                      ":" + oldnick + " NICK :" + newnick
#define RPL_JOIN(source, channel)                       ":" + source + " JOIN :" + channel
#define RPL_PRIVMSG(source, target, message)            ":" + source + " PRIVMSG " + target + " " + message
//#define RPL_NOTICE(source, target, message)             ":" + source + " NOTICE " + target + " :" + message
#define RPL_KICK(source, channel, target, reason)       ":" + source + " KICK " + channel + " " + target + " " + reason
#define RPL_PART(source, channel)                       ":" + source + " PART " + channel
#define RPL_QUIT(source, message)                       ":" + source + " QUIT " + message
#define RPL_MODE(source, channel, modes, params)        ":" + source + " MODE " + channel + " " + modes + " " + params
#define RPL_PING(source, token)                         ":" + source + " PONG :" + token

//Utils functions
void            printError(const std::string errorMsg);
bool            channelExists(std::map<std::string, Channel*> channels, std::string name);
bool 			isValidChannelName(const std::string &name);
Command         parseCmd(std::string input);
std::string     ft_itoa(int i);
int             ft_stoi(std::string str);

class NotAnIntException : public std::exception // pour hériter des exceptions de la std
{
    public:
        virtual const char *what() const throw()
        {
            return ("Exception: Not an int.");	//personnalisez votre message qui servira de valeur de retour.
        }
};

#endif