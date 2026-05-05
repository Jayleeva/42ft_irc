#include "../include/Channel.hpp"
#include "../include/Client.hpp"

Channel::Channel(const std::string &name)
	: _name(name),
	  _hasTopic(false),
	  _inviteOnly(false),
	  _topicRestricted(false),
	  _hasUserLimit(false),
	  _userLimit(0),
      _hasKey(false)
{
}

const std::string& Channel::getName() const
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
    if (!client)
		return ;
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
	if (!client)
		return ;
	_members.erase(client);
	_operators.erase(client);
	_invited.erase(client);
}

bool Channel::hasMember(Client *client) const
{
    if (!client)
		return false;
    return (_members.find(client) != _members.end());
}

bool Channel::isEmpty() const
{
    return (_members.empty());
}

const std::set<Client*>& Channel::getMembers() const
{
    return (_members);
}

bool Channel::isInvited(Client *client) const
{
	if (!client)
		return false;
	if (_invited.find(client) != _invited.end())
		return true;
	return false;
}

void Channel::invite(Client *client)
{
	if (!client)
		return ;
	_invited.insert(client);
}

void Channel::removeInvite(Client *client)
{
	if (!client)
		return ;
	_invited.erase(client);
}

void Channel::setTopic(const std::string &topic)
{
	_topic = topic;
	_hasTopic = true;
}

const std::string& Channel::getTopic() const
{
	return _topic;
}

bool Channel::hasTopic() const
{
	return _hasTopic;
}

bool Channel::isInviteOnly() const
{
	return _inviteOnly;
}

void Channel::setInviteOnly(bool status)
{
	_inviteOnly = status;
}

bool Channel::isTopicRestricted() const
{
	return _topicRestricted;
}

void Channel::setTopicRestricted(bool status)
{
	_topicRestricted = status;
}

void Channel::addOperator(Client *client)
{
	if (!client)
		return;
	_operators.insert(client);
}

void Channel::removeOperator(Client *client)
{
	if (!client)
		return;
	_operators.erase(client);
}

bool Channel::isOperator(Client *client) const
{
	if (!client)
		return false;
	if (_operators.find(client) != _operators.end())
		return true;
	return false;
}

void Channel::setUserLimit(int limit)
{
	if (limit <= 0)
		return;
	_userLimit = limit;
	_hasUserLimit = true;
}

int Channel::getUserLimit() const
{
	return _userLimit;
}

void Channel::removeUserLimit()
{
	_hasUserLimit = false;
	_userLimit = 0;
}

bool Channel::hasUserLimit() const
{
	return _hasUserLimit;
}

bool Channel::isFull() const
{
	if (!_hasUserLimit)
		return false;
	if ((int)_members.size() >= _userLimit)
		return true;
	return false;
}

bool Channel::hasKey() const
{
	return _hasKey;
}

void Channel::setKey(const std::string &key)
{
	if (key.empty())
		return ;
	_key = key;
	_hasKey = true;
}

void Channel::removeKey()
{
	_key.clear();
	_hasKey = false;
}

bool Channel::checkKey(const std::string &key) const
{
	if (!_hasKey)
		return true;
	if (_key == key)
		return true;
	return false;
}
