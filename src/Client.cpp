#include "../include/Client.hpp"

Client::Client()
	: _fd(-1),
	  _registered(false),
	  _hasNick(false),
	  _hasUser(false),
	  _hasPass(false)
{
}

Client::Client(std::map<std::string, Channel*> channels, int fd)
    : _fd(fd),
      _registered(false),
      _hasNick(false),
      _hasUser(false),
      _hasPass(false)
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

const std::string& Client::getNickname() const
{
    return _nickname;
}

const std::string& Client::getUsername() const
{
    return _username;
}

const std::string& Client::getHostname() const
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
    _hostname = hostname;
}

void Client::tryRegister()
{
    if (_hasNick && _hasUser && _hasPass)
        _registered = true;
}

void Client::addChannel(const std::string &channelName)
{
    if (channelName.empty())
		return ;
    _channels.insert(channelName);
}

void Client::removeChannel(const std::string &channelName)
{
    if (channelName.empty())
		return ;
    _channels.erase(channelName);
}

/*bool Client::isInChannel(const std::string &channelName) const    //NOTE: plus besoin car chaque client n'a pas de liste
{
    if (channelName.empty())
		return false;
    return (_channels.find(channelName) != _channels.end());
}*/