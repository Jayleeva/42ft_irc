#include "../include/Client.hpp"

Client::Client() {};

Client::Client(int fd) : _fd(fd), _registered(false), _hasNick(false), _hasUser(false), _hasPass(false)
{
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

bool Client::hasPass() const
{
    return (_hasPass);
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

void Client::setPassValid()
{
    _hasPass = true;
    tryRegister();
}

void    Client::setHostname(const std::string &hostname)
{
    this->_hostname = std::string(hostname);
}

void Client::tryRegister()
{
    if (_hasNick && _hasUser && _hasPass)
        _registered = true;
}

void Client::addChannel(const std::string &channelName)
{
    _channels.insert(channelName);
}

void Client::removeChannel(const std::string &channelName)
{
    _channels.erase(channelName);
}

bool Client::isInChannel(const std::string &channelName) const
{
    return (_channels.find(channelName) != _channels.end());
}