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

//parsing functions
std::string getCommand(const std::string& msg);

//Utils functions
bool isEmptyArg(const std::string &arg);
std::string getArgument(const std::string& msg);
void printError(const std::string& errorMsg);

#endif