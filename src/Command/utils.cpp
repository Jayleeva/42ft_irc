#include "../../include/utils.hpp"

//This function check if the field is empty or not
bool isEmptyArg(const std::string &arg)
 {
    size_t i = 0;

    while (i < arg.size())
    {
        if (arg[i] != ' ')
            return false;
        i++;
    }
    return true;
 }

 //This function is used to retrieve the argument of the command.
 std::string getArgument(const std::string& msg)
 {
    size_t pos = msg.find(' ');

    if (pos == std::string::npos)
        return ("");
    return (msg.substr(pos + 1));
 }

//This function is used to retrieve the client fd using its username. If it didn't find it, it returns -1.
int   findClientByName(std::map<int, Client*> _clients, std::string name)
{
   int   res;
	std::map<int, Client*>::iterator it;
	for (it = _clients.begin(); it != _clients.end(); it ++)
	{
		if (it->second->getUsername() == name)
      {
			res = it->first;
         break;
      }
	}
	if (it == _clients.end())
		res = -1;
   return (res);
}

 /*
 **find() : is a function to find something, if its found return the index
    if not return `npos`.
 */

 void printError(const std::string& errorMsg)
 {
    std::cout << "Error: " << errorMsg << std::endl;
 }