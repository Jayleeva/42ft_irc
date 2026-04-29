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

std::set<Client*>   Channel::getMembers() const
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

std::string getAllMembers(std::set<Client*> members)
{
    std::string res = " :[";
    res += RPL_NAMREPLY;
    
    size_t         i = 0;
    for (std::set<Client*>::iterator it = members.begin(); it != members.end(); it ++)
    {
        std::string nickName = (*it)->getNickname();
        std::string trimmedName = nickName.substr(0, strlen(nickName.c_str()) - 1);
        std::cout << "trimmedName nick = " << trimmedName << std::endl;
        res += nickName;
        if (i + 1 < members.size())
        {
            res += " ";
            res += RPL_NAMREPLY;
        }
        i ++;
    }
    res += "]";
    return (res);
}

void Channel::addMember(Client *client)
{
    _members.insert(client);
    
    /*std::string cmd = "JOIN ";
    std::string msg;
    std::string trimmedName = _name.substr(0, strlen(_name.c_str()) - 1);
    std::cout << "trimmedName channel = " << trimmedName << std::endl;
    std::string list = getAllMembers(_members);
    //msg = cmd + trimmedName + list;
    std::cout << "msg = " << cmd << trimmedName << list << std::endl;

    ssize_t bytes = send(client->getFd(), msg.c_str(), strlen(msg.c_str()), 0);
    std::cout << GREEN << bytes << DEFAULT << std::endl;

    cmd = "TOPIC ";
    msg = cmd + trimmedName + RPL_ENDOFNAMES;
    send(client->getFd(), msg.c_str(), strlen(msg.c_str()), 0);*/
}

void Channel::removeMember(Client *client)
{
    _members.erase(client);
}

bool Channel::hasMember(Client *client) const
{
    return (_members.find(client) != _members.end());
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