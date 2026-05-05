#include "../include/utils.hpp"


 /*
 **find() : is a function to find something, if its found return the index
    if not return `npos`.
 */

void printError(const std::string& errorMsg)
{
   std::cout << "Error: " << errorMsg << std::endl;
}

void sendChannelRPL(Channel *chan, std::string RPL, Client &client)
{
    std::string msg = chan->getName() + RPL;
    send(client.getFd(), msg.c_str(), strlen(msg.c_str()), 0);
}


 bool isValidChannelName(const std::string &name)
{
    size_t i;

    if (name.empty())
        return (false);
    if (name[0] != '#' && name[0] != '&')
        return (false);
    if (name.length() > 200)
        return (false);

    i = 0;
    while (i < name.length())
    {
        if (name[i] == ' ' || name[i] == ',' || name[i] == 7)
            return (false);
        i++;
    }
    return (true);
}