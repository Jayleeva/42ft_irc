//------------ COMPILER ET EXECUTER A PART ------------

#include <iostream>

#include <arpa/inet.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

# define PORT 6667

void	safeGetline(std::string &input)
{
	getline(std::cin, input);
	if (std::cin.eof())
		exit(0);
}

int main(void)
{

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0)
    {
        perror("socket failed");
        return (1);
    }

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons((u_short)PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) <= 0)
    {
        perror("Invalid address/ Address not supported");
        return 1;
    }

    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
    {
        perror("connect failed");
        return (1);
    }

    char buffer[1024] = { 0 };
    read(clientSocket, buffer,
                   1024 - 1);
    printf("%s\n", buffer);

    std::string cmd;
    while (true)
    {
		std::cout << "> Enter command :" << std::endl;
		safeGetline(cmd);
        if (cmd.empty())
            continue ;
        else if (cmd == "EXIT")
            break;
        else
            send(clientSocket, cmd.c_str(), strlen(cmd.c_str()), 0);
    }

    close(clientSocket);
    return (0);
}