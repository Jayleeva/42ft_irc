#ifndef COMMAND_HPP
# define COMMAND_HPP

#include <iostream>
#include <string>

#include "Message.hpp"
#include "utils.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"

#define CMD_INVITE "INVITE"
#define CMD_PASS "PASS"
#define CMD_JOIN "JOIN"
#define CMD_KICK "KICK"
#define CMD_MODE "MODE"
#define CMD_NICK "NICK"
#define CMD_PRIVMSG "PRIVMSG"
#define CMD_QUIT "QUIT"
#define CMD_TOPIC "TOPIC"
#define CMD_USER "USER"
#define CMD_PART "PART"

//This class is used to represent the IRC command contained in the Message.
class Command
{
    private:
        std::string _cmd;

        void pass(Message const &msg, Client &client, Server &server);
        void nick(Message const &msg, Client &client, Server &server);
        void user(Message const &msg, Client &client, Server &server);
        void join(Message const &msg, Client &client, Server &server);
        void part(Message const &msg, Client &client, Server &server);
        void privmsg(Message const &msg, Client &client, Server &server);
        // void invite(Message const &msg, Client &client, Server &server);
        // void kick(Message const &msg, Client &client, Server &server);
        // void topic(Message const &msg, Client &client, Server &server);
        // void mode(Message const &msg, Client &client, Server &server);
        // void quit(Message const &msg, Client &client, Server &server);
    
    public:
        Command();
        Command(const std::string& cmd);
        virtual ~Command();

        std::string getCmd() const;
        void setCmd(const std::string& cmd);

        void execute(Message const &msg, Client &client, Server &server);

};

#endif

/*
**getCmd: Method of Command class, return the command already stored in the object
**getCommand : Parsing function, extract the command from the raw message
*/