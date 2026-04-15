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
 /*
 **find() : is a function to find something, if its found return the index
    if not return `npos`.
 */

 void printError(const std::string& errorMsg)
 {
    std::cout << "Error: " << errorMsg << std::endl;
 }