#include "../include/Channel.hpp"
#include "../include/Client.hpp"

Channel::Channel(const std::string &name) : _name(name)
{
    this->_access.inviteOnly = false;
    this->_access.userLimit = 0;
    this->_access.hasKey = false;
    this->_access.key = "";
}

std::string Channel::getName() const
{
    return _name;
}

t_access Channel::getAccess() const
{
    return _access;
}

void Channel::setAccess(t_access access)
{
    this->_access = access;
}
void Channel::setOnInvite(bool inviteOnly)
{
    this->_access.inviteOnly = inviteOnly;
}

void    Channel::setUserLimit(int userLimit)
{
    this->_access.userLimit = userLimit;
}

void    Channel::setKey(std::string key)
{
    this->_access.key = key;
    if (!key.empty())
        this->_access.hasKey = true;
    else
        this->_access.hasKey = false;
}
        
void    Channel::setTopic(t_topic topic)
{
    this->_topic = topic;
}

void    Channel::setSubject(std::string subject)
{
    this->_topic.subject = subject;
}
void    Channel::setRestricted(bool restricted)
{
    this->_topic.restricted = restricted;
}

void Channel::addMember(Client *client)
{
    _members.insert(client);
}

void Channel::removeMember(Client *client)
{
    _members.erase(client);
}

bool Channel::hasMember(Client *client) const
{
    return (_members.find(client) != _members.end());
}