#include "../include/Channel.hpp"
#include "../include/Client.hpp"

Channel::Channel(const std::string &name) : _name(name)
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
    _members.erase(client);
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