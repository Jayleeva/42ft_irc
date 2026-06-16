#include "../include/utils.hpp"
#include "../include/Command.hpp"

Command parseCmd(std::string input)
{
    Command cmd;
    std::vector<std::string>	parsing;
	std::string			        element;
    std::stringstream 	        ss(input);

	while (getline(ss, element, ' '))
		parsing.push_back(element);
    
    cmd.setParsing(parsing);
    return (cmd);
}