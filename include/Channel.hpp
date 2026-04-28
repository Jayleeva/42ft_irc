#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <set>
#include <vector>
#include <sys/socket.h>
#include <bits/stdc++.h>
#include <string.h>

class Client;

typedef struct s_access
{
    bool        inviteOnly;
    int         userLimit; // si set a 0, pas de limite
    bool        hasKey;
    std::string key;
}               t_access;

typedef struct s_topic
{
    std::string subject;
    bool        restricted;
}               t_topic;

class Channel
{
    private:
        std::string _name;
        std::vector<Client*> _members;
        std::set<Client*> _operators;
        std::set<Client*> _kickbanned;
        t_access    _access;
        t_topic     _topic;

    public:
        Channel(const std::string &name);
    
        std::string getName() const;
        std::vector<Client*>   getMembers() const;
        std::set<Client*>   getOperators() const;  

        t_access    getAccess() const;
        //bool        getOnInvite() const;
        //int         getUserLimit() const;
        //std::string getKey() const;
        t_topic     getTopic() const;

        void    setAccess(t_access access);
        void    setOnInvite(bool inviteOnly);
        void    setUserLimit(int userLimit);
        void    setKey(std::string key);

        void    setTopic(t_topic topic);
        void    setSubject(std::string subject);
        void    setRestricted(bool restricted);

        void addMember(Client *client);
        void removeMember(Client *client);
        bool hasMember(Client *client);

        void addOperator(Client *client);
        void removeOperator(Client *client);
        bool hasOperator(Client *client) const;

};

#endif