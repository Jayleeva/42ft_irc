#ifndef UTILS_HPP
# define UTILS_HPP

#include <iostream>
#include <string>
#include "Client.hpp"

//Colors
# define DEFAULT "\001\033[0;39m\002"
# define YELLOW "\001\033[1;93m\002"
# define RED "\001\033[0;31m\002"
# define GREEN "\001\033[1;32m\002"
# define MAG  "\001\033[1;35m\002"

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
int findClientByName(std::map<int, Client*> _clients, std::string name);
#endif