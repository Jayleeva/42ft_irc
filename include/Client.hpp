#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <set>
#include <map>
#include "Channel.hpp"

# define NON_MEMBER_STATUS 0
# define MEMBER_STATUS 1
# define OPERATOR_STATUS 2 
# define KICKED_STATUS 3

class Client
{
    private:
        int _fd;
        std::string _nickname;
        std::string _username;
        std::string _hostname;
        bool _registered;
        bool _hasNick;
        bool _hasUser;
        bool _hasPass;
        std::set<std::string> _channels;
    
    public:
        Client();
        Client(std::map<std::string, Channel*> channels, int fd);

        int getFd() const;
        std::string getNickname() const;
        std::string getUsername() const;
        std::string getHostname() const;
        bool isRegistered() const;

        void setNickname(const std::string &nickname);
        void setUsername(const std::string &username);
        void setHostname(const std::string &hostname);
        void tryRegister();

        void addChannel(const std::string &channelName);
        void removeChannel(const std::string &channelName);
};

#endif