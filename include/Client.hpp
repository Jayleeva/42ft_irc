#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <set>

class Channel;

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
        bool _needRename;
        std::set<std::string> _channels;
    
    public:
        Client();
        Client(int fd);

        int getFd() const;
        const std::string& getNickname() const;
        const std::string& getUsername() const;
        const std::string& getHostname() const;
        const std::string getPrefix() const;
        bool isRegistered() const;
        bool getNeedRename() const;

        int setNickname(const std::string &nickname);
        void setUsername(const std::string &username);
        void setHostname(const std::string &hostname);
        void setNeedRename(bool need);
        
        bool hasPass() const;
        bool hasNick() const;
        void setPassValid();
        void tryRegister();

        void addChannel(const std::string &channelName);
        void removeChannel(const std::string &channelName);
        bool isInChannel(const std::string &channelName) const;
};

#endif