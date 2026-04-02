#include "../include/Client.hpp"

Client::Client(int fd) : _fd(fd), _registered(false)
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

bool Client::isRegistered() const
{
    return _registered;
}

void Client::setNickname(const std::string &nickname)
{
    _nickname = nickname;
}

void Client::setUsername(const std::string &username)
{
    _username = username;
}

void Client::setRegistered(bool registered)
{
    _registered = registered;
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