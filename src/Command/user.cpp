#include "../../include/Command.hpp"

/*
**This command allows to choose a client username.
**The server must:
    check that the username is not empty
    check if there is no invalid char
    check that it is not already taken by another client
    save this username in the `Client` object
*/

void Command::user(std::vector<std::string> parsing, Client &client)
{
    if (parsing.size() < 2)
    {
        printError(ERR_NEEDMOREPARAMS);
        return ;
    }

    std::string arg = *(parsing.begin() + 1);
    
    client.setUsername(arg); 
}
