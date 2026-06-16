#include "../include/utils.hpp"

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

void printError(const std::string errorMsg)
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

std::string ft_itoa(int i)
{
  std::stringstream ss;
  std::string str;

  ss << i << std::endl;
  ss >> str;
  return str;
}

int  ft_stoi(std::string str)
{
    long res = 0;
    long l = 1;
    int last = 0;
    if (str[0] == '-')
    {
        last ++;
        l = -1;
    }
    for (int i = str.length() -1; i >= last; i --)
    {
        if ((i == 0 && !isdigit(str[i]) && str[i] != '-' && str[i] != '+') || (i > 0 && !isdigit(str[i])))
            throw NotAnIntException();
        res += (str[i] - '0') * l;
        l *= 10;
        if (res > MAX_INT || res < MIN_INT)
            throw NotAnIntException();
    }
    return (static_cast<int>(res));
}

std::vector<std::string> getAllTargets(std::string list)
{
    std::vector<std::string>    res;

	std::string			        element;
    std::stringstream 	        ss(list);

	while (getline(ss, element, ','))
		res.push_back(element);
    return (res);
}

std::string    rebuildMessage(std::vector<std::string>::iterator it, std::vector<std::string>::iterator ite)
{
    std::string res = "";

    for (std::vector<std::string>::iterator its = it; its != ite; its ++)
    {
        res.append(*its);
        if (its + 1 != ite)
            res.append(" ");
    }
    return (res);
}