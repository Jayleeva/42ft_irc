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

//C'est une première version de la fonction
void Command::pass(Message const &msg, Client &client)
{
    std::string arg = getArgument(msg.getMsg());

    if (isEmptyArg(arg))
    {
        printError(ERR_PARAMS);
        return ;
    }
    (void)client; //à modififer par la suite
}