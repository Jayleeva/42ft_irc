#include "../include/Channel.hpp"
#include "../include/Client.hpp"
#include "../include/utils.hpp"

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

std::vector<Client*>   Channel::getMembers() const
{
    return _members;
}

std::set<Client*>   Channel::getOperators() const
{
    return _operators;
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

t_topic     Channel::getTopic() const
{
    return (this->_topic);
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

std::string getAllMembers(std::vector<Client*> members)
{
    std::string tmp = "[@|+]";
    std::string res = " :[" + tmp;
    for (std::vector<Client*>::iterator it = members.begin(); it != members.end(); it ++)
    {
        res += (*it)->getNickname();
        if (it + 1 != members.end())
        {
            res += " ";
            res += tmp;
        }
    }
    res += "]";
    return (res);
}

void Channel::addMember(Client *client)
{
    _members.insert(_members.end(), client);
    
    std::string msg;
    msg = _name + " :" +  _topic.subject;
    send(client->getFd(), msg.c_str(), strlen(msg.c_str()), 0);
    msg = _name + getAllMembers(_members);
    send(client->getFd(), msg.c_str(), strlen(msg.c_str()), 0);
}

void Channel::removeMember(Client *client)
{
    std::vector<Client*>::iterator it = find(_members.begin(), _members.end(), client);
    if (it != _members.end())
    {
        printError("member does not exist");
        return ;
    }
    _members.erase(it);
}

bool Channel::hasMember(Client *client)
{
    std::vector<Client*>::iterator it = find(_members.begin(), _members.end(), client);
    if (it != _members.end())
    {
        return (true);
    }
    return (false);
}

void Channel::addOperator(Client *client)
{
    _operators.insert(client);
}

void Channel::removeOperator(Client *client)
{
    _operators.erase(client);
}

bool Channel::hasOperator(Client *client) const
{
    return (_operators.find(client) != _operators.end());
}