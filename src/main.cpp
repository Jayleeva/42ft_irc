#include "../include/Server.hpp"
#include "../include/Client.hpp"
#include "../include/Channel.hpp"
#include <iostream>

#include "../include/Server.hpp"
#include "../include/utils.hpp"

bool g_running = true;

void handle_sigint(int sig)
{
    (void)sig;
    g_running = false;
}

void runServer(Server *serv)
{
    serv->setBeforeRun();
    while (g_running)
    {
        if (serv->run())
            break;
    }
}

int isAddressValid(std::string address)
{
    std::vector<std::string>	parsing;
	std::string			        element;
    std::stringstream 	        ss(address);

	while (getline(ss, element, '.'))
		parsing.push_back(element);
    
    if (parsing.size() != 4)
        return (0);

    for (std::vector<std::string>::iterator it = parsing.begin(); it != parsing.end(); it ++)
    {
        try
        {
            int tmp = ft_stoi(*it);
            if (tmp < 0 || tmp > 255)
                return (0);
        }
        catch(const std::exception& e)
        {
            return (0);
        }
    }
    return (1);
}

int main (int argc, char **argv)
{
    Server          serv;
    std::string     password;
    int             port;
    std::string     address;

    if (argc != 4)
    {
        printError("Missing parameters. Expected: ./ircserv <IP address> <port> <password>.");
        return (1);
    }

    password = argv[3];
    if (password.length() < 0 || password.length() > 510)
    {
        printError("Password can't be empty nor longer than 510 chars (UTF-8).");
        return (1);
    }
    serv.setPassword(password);

    try
    {
        port = ft_stoi(argv[2]);
        if (port < 0 || port > 65535)
        {
            printError("Invalid port number. Available ports for IRC range from 6665 to 6669. Suggested port: 6667");
            return (1);
        }
    }
    catch(const std::exception& e)
    {
        printError("Invalid port number. Available ports for IRC range from 6665 to 6669. Suggested port: 6667");
        return (1);
    }

    address = argv[1];
    if (!isAddressValid(address))
    {
        printError("Invalid address. Expected V4 (ex: 127.0.0.1).");
        return (1);
    }

    struct sigaction sa;
    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);

    address = "0.0.0.0"; // par defaut, permet acces au serveur a toutes adresses IP qui peuvent se connecter a la mienne
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons((u_short)port);
    inet_pton(AF_INET, address.c_str(), &(addr.sin_addr));// addr.sin_addr.s_addr = INADDR_ANY; 
    memset(&(addr.sin_zero), 0, 8);

    serv.openSocket(&addr);
    runServer(&serv);
    serv.closeSockets();

    return (0);
}