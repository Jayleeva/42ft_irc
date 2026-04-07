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

        std::set<std::string> _channels; // channels auxquels le client appartient

    public:
        Client(int fd);
        ~Client();

        int getFd() const;
};

#endif