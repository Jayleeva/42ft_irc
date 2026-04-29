#include "../../include/Command.hpp"

/*
**This command allows authentication by providing the server password.
**The server compares the password entered at startup.
** The steps of the function :
    1. Retrieve the complete message
    2. Extract the argument after PASS
    3. Verify if this argument actually exists
        If the argument is empty → an error must be reported.
        If it's correct:
        → The client is marked as having provided the correct password.     
*/

void Command::pass(std::vector<std::string> parsing, Client &client, const std::string password)
{
    if (parsing.size() < 2)
    {
        printError(ERR_NEEDMOREPARAMS);
        return ;
    }

    std::string arg = *(parsing.begin() + 1);

    if (client.isRegistered())
    {
        printError(ERR_ALREADYREGISTRED);
        return;
    }

    if (arg != password) // fonction a creer
    {
        printError(ERR_PASSWDMISMATCH);
        return ;
    }

    client.tryRegister();
}