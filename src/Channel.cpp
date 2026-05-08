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

void Channel::addMember(Client *client)
{
    if (!client)
		return ;
    _members.insert(client);
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

const std::set<Client*>& Channel::getOperators() const
{
    return _operators;
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

std::string Channel::listAllUsers(std::string newClient)
{
    std::string list = _name + " :";
    
    size_t         i = 0;
    for (std::set<Client*>::iterator it = _members.begin(); it != _members.end(); it ++)
    {
        std::string nickName = (*it)->getNickname();
		list += '[';
		if (newClient.empty())
			list += '@';
		else if (newClient == nickName)
			list += '+';
		list += ']';
        list += nickName;
		if (i + 1 < _members.size())
			list += ' ';
        i ++;
    }
	list += '*';
	return (list);
}