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
    std::cout << "PASS handler called" << std::endl;

    std::string arg = getArgument(msg.getMsg());
    std::string password = getTarget(arg);

    if (isEmptyArg(password))
    {
        printError(ERR_NEEDMOREPARAMS);
        return ;
    }

    if (client.isRegistered())
    {
        printError(ERR_REGISTRED);
        return;
    }

    if (password != server.getPassword())
    {
        printError(ERR_PASSWDMISMATCH);
        return ;
    }

    client.setPassValid();
}