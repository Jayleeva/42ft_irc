#include "../include/Client.hpp"
#include "../include/Channel.hpp"
#include "../include/Server.hpp"

Client::Client() {};

Client::Client(std::map<std::string, Channel*> channels, int fd) : _fd(fd), _registered(false), _hasNick(false), _hasUser(false), _hasPass(false)
{
    for (std::map<std::string, Channel*>::iterator it = channels.begin(); it != channels.end(); it ++)
    {
        this->_channels.insert(it->first);
    }
}

int Client::getFd() const
{
    return _fd;
}

std::string Client::getNickname() const
{
    return _nickname;
}

std::string Client::getUsername() const
{
    return _username;
}

std::string Client::getHostname() const
{
    return _hostname;
}


bool Client::isRegistered() const
{
    return _registered;
}

void Client::setNickname(const std::string &nickname)
{
    _nickname = nickname;
    _hasNick = true;
    tryRegister();
}

void Client::setUsername(const std::string &username)
{
    _username = username;
    _hasUser = true;
    tryRegister();
}

void    Client::setHostname(const std::string &hostname)
{
    this->_hostname = std::string(hostname);
}

void Client::tryRegister()
{
    if (_hasNick && _hasUser)
        _registered = true;
}

void Client::addChannel(const std::string &channelName)
{
    this->_channels.insert(channelName);
}

void Client::removeChannel(const std::string &channelName)
{
    this->_channels.erase(channelName);
}