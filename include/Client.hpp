#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <set>

class Client
{
    private:
        int _fd;
        std::string _nickname;
        std::string _username;
        bool _registered;
        bool _hasNick;
        bool _hasUser;
        std::set<std::string> _channels;

    public:
        Client(int fd);

        int getFd() const;
        std::string getNickname() const;
        std::string getUsername() const;
        bool isRegistered() const;

        void setNickname(const std::string &nickname);
        void setUsername(const std::string &username);

        void tryRegister();

        void addChannel(const std::string &channelName);
        void removeChannel(const std::string &channelName);
        bool isInChannel(const std::string &channelName) const;
};

#endif