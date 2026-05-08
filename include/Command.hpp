#ifndef COMMAND_HPP
# define COMMAND_HPP

#include <iostream>
#include <string>
#include <vector>

#include "utils.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"

#define CMD_CAP "CAP"
#define CMD_PING "PING"

//authenticate, set nickname, set username
#define CMD_PASS "PASS"         // "/auth" ?
#define CMD_USER "USER"         // "/set irc.server.ircserv.username" ?
#define CMD_NICK "NICK"         // "/nick <nickname>"

//join a channel, send and receive private msg
#define CMD_JOIN "JOIN"         // "/join <channel>"
#define CMD_PRIVMSG "PRIVMSG"   // "/query <nickname>"

#define CMD_PART "PART"         // "/part <channel>" // pas demandé; QUIT et DISCONNECT gérés par le client par signaux
#define CMD_QUIT "QUIT"
//operators only
#define CMD_KICK "KICK"         // "/kick <channel> <nickname>"
#define CMD_INVITE "INVITE"     // "/invite <channel> <nickname>"
#define CMD_TOPIC "TOPIC"       // "/topic <channel> [<newtopic>]"
#define CMD_MODE "MODE"         // "/mode <channel> <flag> [<arg>]" -- si pas de flag, montre juste les param actuels?


//This class is used to represent the IRC command contained in the Message.
class Command
{
    private:
        std::vector<std::string>    _parsing;

        void pass(std::vector<std::string> parsing, Client &client, Server &server);
        void nick(std::vector<std::string> parsing, Client &client, Server &server);
        void user(std::vector<std::string> parsing, Client &client, Server &server);
        void join(std::vector<std::string> parsing, Client &client, Server &server);
        void invite(std::vector<std::string> parsing, Client &client, Server &server);
        void kick(std::vector<std::string> parsing, Client &client, Server &server);
        void topic(std::vector<std::string> parsing, Client &client, Server &server);
        void mode(std::vector<std::string> parsing, Client &client, Server &server);
        void privmsg(std::vector<std::string> parsing, Client &client, Server &server);
        void part(std::vector<std::string> parsing, Client &client, Server &server);
    
    public:
        Command();
        Command(std::vector<std::string> parsing);
        virtual ~Command();

        std::vector<std::string> getParsing() const;
        void    setParsing(std::vector<std::string> parsing);

        void execute(Client &client, Server &server);

};

#endif

/*
**getCmd: Method of Command class, return the command already stored in the object
**getCommand : Parsing function, extract the command from the raw message
*/