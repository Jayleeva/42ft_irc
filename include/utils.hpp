#ifndef UTILS_HPP
# define UTILS_HPP

#include <iostream>
#include <string>

//Error messages
#define ERR_PASSWDMISMATCH "Password incorrect"
#define ERR_NEEDPASS "Password required"
#define ERR_CMD "Unknown command"
#define ERR_ERRONEUSNICKNAME "Erroneus nickname"
#define ERR_NICKNAMEINUSE "Nickname is already in use"
#define ERR_NEEDMOREPARAMS "Not enough parameters"
#define ERR_REGISTRED "Already registered"
#define ERR_USERONCHANNEL "User is already on channel"
#define ERR_CHANNELISFULL "Cannot join channel : channel is full"
#define ERR_BANNEDFROMCHAN "Cannot join channel : banned from channel"
#define ERR_INVITEONLYCHAN "Cannot join channel : invite only channel"
#define ERR_REGISTRED "Already registered"
#define ERR_NOTREGISTERED "You have not registered"
#define ERR_BADCHANNELNAME "Bad channel name"
#define ERR_NOTEXTTOSEND "No text to send"
#define ERR_NOSUCHCHANNEL "No such channel"
#define ERR_CANNOTSENDTOCHAN "Cannot send to channel"
#define ERR_NOSUCHNICK "No such nickname"

//Colors
# define DEFAULT "\001\033[0;39m\002"
# define YELLOW "\001\033[1;93m\002"
# define RED "\001\033[0;31m\002"
# define GREEN "\001\033[1;32m\002"
# define MAG  "\001\033[1;35m\002"

//parsing functions
std::string getCommand(const std::string& msg);
std::string getArgument(const std::string& msg);
// std::string getTarget(const std::string& args); //à faire
// std::string getMessage(const std::string& args); //à faire

//Utils functions
bool isEmptyArg(const std::string &arg);
void printError(const std::string& errorMsg);
bool isValidChannelName(const std::string &name);

#endif