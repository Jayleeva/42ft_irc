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

void Command::pass(Message const &msg, Client &client, Server &server)
{
    std::string arg = getArgument(msg.getMsg());

    size_t i = 0;
    while (i < arg.size() && arg[i] == ' ')
        i++;
    arg = arg.substr(i);

    if (isEmptyArg(arg))
    {
        printError(ERR_NEEDMOREPARAMS);
        return ;
    }

    size_t pos = arg.find(' ');
    if (pos != std::string::npos)
        arg = arg.substr(0, pos);

    if (client.isRegistered())
    {
        printError(ERR_REGISTRED);
        return;
    }

    if (arg != server.getPassword()) // fonction a creer
    {
        printError(ERR_PASSWDMISMATCH);
        return ;
    }

    client.tryRegister(true);
}