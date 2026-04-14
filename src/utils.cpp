#include "../include/utils.hpp"

void printError(std::string msg)
{
    std::cerr << RED << msg << DEFAULT << std::endl;
}

/*void printMap(std::map<int, Client*> map)
{
    for(std::map<int, Client*>::const_iterator it = map.begin();
    it != map.end(); ++it)
    {
        std::cout << it->first << " " << it->second.first << " " << it->second.second << "\n";
    }
}*/