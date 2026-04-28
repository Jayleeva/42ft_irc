#include "../include/Channel.hpp"
#include "../include/Client.hpp"

Channel::Channel(const std::string &name) : _name(name), _hasTopic(false), _inviteOnly(false), _topicRestricted(false)
{
}

std::string Channel::getName() const
{
    return _name;
}

void Channel::addMember(Client *client)
{
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