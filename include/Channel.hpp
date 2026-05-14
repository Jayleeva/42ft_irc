#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <set>
#include <vector>
#include <sys/socket.h>
#include <string.h>

#include "utils.hpp"

class Client;

class Channel
{
    private:
        std::string         _name;
        std::set<Client*>   _members;
        std::set<Client*>   _operators;
        std::set<Client*>   _invited;
        std::string         _topic;
        bool                _hasTopic;
        bool                _inviteOnly;
        bool                _topicRestricted;
        bool                _hasUserLimit;
        int                 _userLimit;
        std::string         _key;
        bool                _hasKey;

    public:
        Channel(const std::string &name);

        const std::string& getName() const;
        const std::set<Client*>& getMembers() const;
        const std::set<Client*>& getOperators() const;
        const std::string& getTopic() const;

        void addMember(Client *client);
        void removeMember(Client *client);
        bool hasMember(Client *client) const;
        bool isEmpty() const;

        bool isInvited(Client *client) const;
        void invite(Client *client);
        void removeInvite(Client *client);

        void setTopic(const std::string &topic);
        bool hasTopic() const;

        bool isInviteOnly() const;
        void setInviteOnly(bool status);

        bool isTopicRestricted() const;
        void setTopicRestricted(bool status);

        void addOperator(Client *client);
        void removeOperator(Client *client);
        bool isOperator(Client *client) const;

        void setUserLimit(int limit);
        int  getUserLimit() const;
        void removeUserLimit();
        bool hasUserLimit() const;
        bool isFull() const;
        
        bool hasKey() const;
        void setKey(const std::string &key);
        void removeKey();
        bool checkKey(const std::string &key) const;

        std::string listAllUsers(std::string newClient);
        
};

#endif