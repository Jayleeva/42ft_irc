#include "../include/utils.hpp"

//This function is used to check if a channel exists.
bool  channelExists(std::map<std::string, Channel*> channels, std::string name)
{
	std::map<std::string, Channel*>::iterator it;
	for (it = channels.begin(); it != channels.end(); it ++)
	{
		if (it->first == name)
      {
         return true;
      }
	}
	return (false);
}

 /*
 **find() : is a function to find something, if its found return the index
    if not return `npos`.
 */

void printError(const std::string& errorMsg)
{
   std::cout << "Error: " << errorMsg << std::endl;
}


 bool isValidChannelName(const std::string &name)
{
    size_t i;

    if (name.empty())
        return (false);
    if (name[0] != '#' && name[0] != '&')
        return (false);
    if (name.length() > 200)
        return (false);

    i = 0;
    while (i < name.length())
    {
        if (name[i] == ' ' || name[i] == ',' || name[i] == 7)
            return (false);
        i++;
    }
    return (true);
}

/*std::string ft_itoa(int i)
{
  std::stringstream ss;
  std::string str;

  ss << i << std::endl;
  ss >> str;
  return str;
}*/