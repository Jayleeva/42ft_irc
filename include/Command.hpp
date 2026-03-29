#ifndef COMMAND_HPP
# define COMMAND_HPP

#include <iostream>
#include <string>

#define CMD_INVITE "INVITE"
#define CMD_JOIN "JOIN"
#define CMD_KICK "KICK"
#define CMD_MODE "MODE"
#define CMD_NICK "NICK"
#define CMD_PRIVMSG "PRIVMSG"
#define CMD_QUIT "QUIT"
#define CMD_TOPIC "TOPIC"
#define CMD_USER "USER"

//This class is used to represent the IRC command contained in the Message.
class Command
{
    private:
        std::string _cmd;
    
    public:
        Command();
        Command(const std::string& cmd);
        ~Command();

        std::string getCmd() const;
        void setCmd(const std::string& cmd);

};

#endif