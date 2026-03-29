#include "../include/Message.hpp"
#include "../include/Command.hpp"

//Main de test
int main()
{
	Message msg("NICK marjorie");
	std::cout << msg.getMsg() << std::endl;

	msg.setMsg("JOIN #42");
	std::cout << msg.getMsg() << std::endl;

    Command cmd("JOIN");
    std::cout << cmd.getCmd() << std::endl;

	return (0);
}