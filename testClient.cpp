//------------ COMPILER ET EXECUTER A PART ------------

#include <iostream>

#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

# define PORT 8080

/*the port is set to 4444, but this value can be changed to any other valid port number between 0 and 65535. The reason for this range is that in TCP and UDP, a port number is represented by a 16-bit unsigned integer, and there are three types of ports.

    Ports 0 to 1023 are reserved for specific services and protocols, such as HTTP (port 80), FTP (port 21), and SSH (port 22). They require administrative privileges to use
    Ports numbered 1024 to 49151 can be registered for specific purposes and are used by non-standard applications and services.
    Dynamic or private ports (49152 to 65535) are used by client applications for outgoing connections. These ports are dynamically allocated by the operating system to clients when they initiate outgoing connections.*/

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
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    const char* message = "Hello, server!";
    send(clientSocket, message, strlen(message), 0);

    close(clientSocket);
    return (0);
}