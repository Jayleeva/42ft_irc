#include "../../include/utils.hpp"

/*
**This function : -Ignore spaces at the beginning
                -Read to the first space
                -Return this section
*/
std::string getCommand(const std::string& msg)
{
    size_t i = 0;
    while (i < msg.size() && msg[i] == ' ')
        i++;
    
    if (i >= msg.size())
        return "";
    
    size_t start = i;

    while (i < msg.size() && msg[i] != ' ')
        i++;
    return msg.substr(start, i - start);
}

 //This function is used to retrieve the argument of the command.
 std::string getArgument(const std::string& msg)
 {
    size_t i = 0;
    while (i < msg.size() && msg[i] == ' ')
        i++;
    
    while (i < msg.size() && msg[i] != ' ')
        i++;
    
    while (i < msg.size() && msg[i] == ' ')
        i++;
    
    if (i >= msg.size())
        return "";
    
    return msg.substr(i);
 }
 