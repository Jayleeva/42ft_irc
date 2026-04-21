#ifndef UTILS_HPP
# define UTILS_HPP

#include <iostream>
#include <string>

//Error messages
#define ERR_PASSWDMISMATCH "Wrong Password"
#define ERR_NEEDPASS "Password required"
#define ERR_CMD "Unknown command"
#define ERR_ERRONEUSNICKNAME "Erroneus nickname"
#define ERR_NICKNAMEINUSE "This Nickname is already used"
#define ERR_NEEDMOREPARAMS "Not enough parameters"
#define ERR_REGISTRED "Already registered"

//parsing functions
std::string getCommand(const std::string& msg);

//Utils functions
bool isEmptyArg(const std::string &arg);
std::string getArgument(const std::string& msg);
void printError(const std::string& errorMsg);

#endif