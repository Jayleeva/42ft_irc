#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <set>

class Client;

class Channel
{
    private:
        std::string _name;
        std::set<Client*> _members;
        std::set<Client*> _operators;

    public:
        Channel(const std::string &name);

        std::string getName() const;

        void addMember(Client *client);
        void removeMember(Client *client);
        bool hasMember(Client *client) const;
};

#endif