#ifndef UTILS_HPP
# define UTILS_HPP

#include <iostream>
#include <map>

# define DEFAULT "\001\033[0;39m\002"
# define YELLOW "\001\033[1;93m\002"
# define RED "\001\033[0;31m\002"
# define GREEN "\001\033[1;32m\002"
# define MAG  "\001\033[1;35m\002"

void    printError(std::string msg);
//void    printMap(std::map<int, Client*> map);

/*template <typename T>
void    printMap(std::map<int, T> map)
{
    for (std::map<int, T>::iterator it = map.begin(); it != map.end(); ++it)
    {
        std::cout << it->first << " " << it->second.first << " " << it->second.second << "\n";
    }
}*/

#endif