#include "../include/utils.hpp"

/*
**This function : -Ignore spaces at the beginning
                -Read to the first space
                -Return this section
 //This function extract the command of the string
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

 
 //This function extract the target of the string
 std::string getTarget(const std::string& args)
 {
    size_t i = 0;
    while (i < args.size() && args[i] == ' ')
        i++;
    
    if (i >= args.size())
        return "";
    
    size_t start = i;

    while (i < args.size() && args[i] != ' ')
        i++;
    return args.substr(start, i - start);
 }

 //This function extract the message of the string
 std::string getMessage(const std::string& args)
 {
    size_t i = 0;
    while (i < args.size() && args[i] == ' ')
        i++;
    
    while (i < args.size() && args[i] != ' ')
        i++;
    
    while (i < args.size() && args[i] == ' ')
        i++;
    
    if (i >= args.size())
        return "";
    
    return args.substr(i);
 }
