#include "../include/Server.hpp"
#include "../include/utils.hpp"
#include "../include/Command.hpp"

Server::Server(): _name("ircserv") {};
Server::~Server()
{
    std::map<int, Client*>::iterator it;
    std::map<std::string, Channel*>::iterator itChannel;

    it = _clients.begin();
    while (it != _clients.end())
    {
        delete it->second;
        it++;
    }
    itChannel = _channels.begin();
    while (itChannel != _channels.end())
    {
        delete itChannel->second;
        itChannel++;
    }
}

int Server::getSocket() const
{
    return (this->_socket);
}

std::map<int, Client*> Server::getMapClients() const
{
    return (this->_clients);
}

std::map<std::string, Channel*> Server::getMapChannels() const
{
    return (this->_channels);
}

std::string Server::getPassword() const
{
    return (this->_password);
}

std::string Server::getName() const
{
    return (this->_name);
}

void    printMap(std::map<int, Client *> map)
{
    for (std::map<int, Client *>::iterator it = map.begin(); it != map.end(); ++it)
    {
        std::cout << "---  " << it->first << " " << it->second << " \n";
    }
}

void    Server::setPassword(std::string password)
{
    this->_password = password;
}

void Server::openSocket(struct sockaddr_in *addr)
{
    int opt = 1;
    this->_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (this->_socket < 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "is created\n";

    if (setsockopt(this->_socket, SOL_SOCKET, SO_REUSEADDR, (const char *) &opt, (sizeof(opt)))) //| SO_REUSEPORT
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    std::cout << "is set\n";

    if (bind(this->_socket, (struct sockaddr*)addr, sizeof(struct sockaddr)) < 0)
    {
        int errsv = errno;
        std::cout << "errno = " << errsv << std::endl;
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
 
    std::cout << "is bound\n";

    if (listen(this->_socket, QUEUE_SIZE) < 0)
    {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
    std::cout << "is listening\n";
}

void    Server::clearClientsMap()
{
    for (std::map<int, Client*>::iterator it = this->_clients.begin(); it != this->_clients.end(); it ++)
    {
        delete (it->second);
    }
    this->_clients.clear();
}

void    Server::closeSockets()
{
    for (size_t i = 0; i < this->_nfd; i++)
    {
        close(this->_fds[i].fd);
    }
    close(this->_socket);
    clearClientsMap();
}

void    Server::addClient()
{
    struct sockaddr_in  clientAddr;
    socklen_t           clientLen = sizeof(clientAddr);

    int clientSocket = accept(this->_socket, (struct sockaddr *)&clientAddr, &clientLen);
    if (clientSocket < 0)
    {
        perror("accept() failed");
        exit(EXIT_FAILURE);
    }

    this->_fds[this->_nfd].fd = clientSocket;
    this->_fds[this->_nfd].events = POLLIN;
    this->_nfd ++;

    Client *newClient = new Client(clientSocket);
    newClient->setHostname(inet_ntoa(clientAddr.sin_addr));
    this->_clients.insert(this->_clients.end(), std::make_pair(clientSocket, newClient));

    std::cout << YELLOW << "Client " << clientSocket << " connected." << DEFAULT << std::endl;

    char    buffer[MAXBYTES];
    memset(buffer, '\0', sizeof(buffer));
    ssize_t nbytes = recv(clientSocket, buffer, sizeof(buffer), MSG_DONTWAIT);
    if (nbytes > 0)
    { 
        buffer[nbytes] = '\0';

        std::stringstream ss(buffer);
        std::string line;

        while (std::getline(ss, line, '\n'))
        {
            if (!line.empty() && line[line.size() - 1] == '\r')
                line.erase(line.size() - 1);
            if (!line.empty())
                execCmd(line, clientSocket);
        }
        std::cout << "add " << RED << nbytes << DEFAULT << std::endl;
        std::cout << "< " << buffer << std::endl;
    }
}

void int_to_char(int num, char *result)
{
    int temp = num;
    int len = 0;

    while (temp > 0) {
        len++;
        temp /= 10;
    }

    for (int i = len - 1; i >= 0; i--) {
        result[i] = num % 10 + '0';
        num /= 10;
    }

    result[len] = '\0';
}

void    Server::removeFromAllChannels(Client *client)
{
    for (std::map<std::string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); it ++)
    {
        if (it->second->hasMember(client))
        {
            if (it->second->isOperator(client))
                it->second->removeOperator(client);
            it->second->removeMember(client);
        }
    }
}

void    Server::removeClient(nfds_t i)
{
    std::map<int, Client*>::iterator    it;

    char result[1024];
    int_to_char(_fds[i].fd, result);

    it = this->_clients.find(_fds[i].fd);
    if (it != this->_clients.end())
    {
        removeFromAllChannels(it->second);
        delete it->second;
        this->_clients.erase(it);
    }

	close(_fds[i].fd);
    std::cout << YELLOW << "Client " << _fds[i].fd << " disconnected." << DEFAULT << std::endl;

	_fds[i].fd = _fds[_nfd -1].fd;
	_fds[i].events = POLLIN;
	_fds[_nfd -1].fd = -1;
    _nfd --;

    std::string message = static_cast<std::string>(result) + " disconnected";
    for (nfds_t j = 1; j < _nfd; j ++)
    {
        std::cout << "'" << message << "'" << " sent to client " << _fds[j].fd << std::endl;
        send(_fds[j].fd, message.c_str(), strlen(message.c_str()), 0);
    }
}


void Server::execCmd(std::string input, int fd)
{
    Command cmd = parseCmd(input);

    cmd.execute(*(this->_clients.find(fd)->second), *this);
}

void    Server::execClient(nfds_t i)
{
    int fd = this->_fds[i].fd;

    char    buffer[MAXBYTES];
    
    memset(buffer, '\0', sizeof(buffer));
    ssize_t nbytes = recv(fd, buffer, sizeof(buffer), MSG_DONTWAIT);
    if (nbytes > 0)
    {
        buffer[nbytes] = '\0';

        std::stringstream ss(buffer);
        std::string line;

        while (std::getline(ss, line, '\n'))
        {
            if (!line.empty() && line[line.size() - 1] == '\r')
                line.erase(line.size() - 1);
            if (!line.empty())
                execCmd(line, fd);
        }
        
        std::cout << "exec " << RED << nbytes << DEFAULT << std::endl;
        std::cout << "< " << buffer << std::endl;
    }
    if (nbytes == 0)
        this->removeClient(i);
}

void    Server::run()
{
    memset(this->_fds, 0, sizeof(this->_fds));
    this->_fds[0].events = POLLIN;
    this->_fds[0].fd = this->_socket;
    this->_nfd = 1;

    while (true)
    {   
        nfds_t currentSize = this->_nfd;
        int ready = poll(this->_fds, currentSize, -1);
        if (ready < 0)
        {
            perror("poll() failed");
            break;
        }
        else if (ready == 0)
        {
            perror(" poll() timed out."); // doit avoir un timeout ou pas?
            break;
        }
        
        for (nfds_t i = 0; i < currentSize; i ++)
        {
            if (this->_fds[i].revents == 0)
                continue;

            else if (this->_fds[i].revents & POLLIN)
            {
                if (this->_fds[i].fd == this->_socket)
                {
                    addClient();
                    break;
                }
                else
                {
                    this->execClient(i);
                }
            }
            else if ((this->_fds[i].revents & POLLHUP) || (this->_fds[i].revents & POLLOUT))
            {
                this->removeClient(i -1);
                break;
            }
        }
    }
}

bool Server::nicknameExists(const std::string &nickname) const
{
    std::map<int, Client*>::const_iterator it;

    it = _clients.begin();
    while (it != _clients.end())
    {
        if (it->second->getNickname() == nickname)
            return (true);
        it++;
    }
    return (false);
}

bool Server::channelExists(const std::string &name) const
{
    return (_channels.find(name) != _channels.end());
}

Channel *Server::getChannel(const std::string &name)
{
    std::map<std::string, Channel*>::iterator it;

    it = _channels.find(name);
    if (it != _channels.end())
        return (it->second);
    return (NULL);
}

Channel *Server::createChannel(const std::string &name)
{
    Channel *newChannel;

    newChannel = new Channel(name);
    _channels.insert(std::make_pair(name, newChannel));
    return (newChannel);
}

void Server::joinClientToChannel(Client *client, const std::string &name)
{
    Channel *channel;

    if (!client)
        return ;
    if (channelExists(name))
        channel = getChannel(name);
    else
    {
        channel = createChannel(name);
        channel->addOperator(client);
    }    
    if (!channel->hasMember(client))
        channel->addMember(client);
    if (!client->isInChannel(name))
        client->addChannel(name);
    sendJoinConfirmation(client, *channel);
}

void Server::removeClientFromChannel(Client *client, const std::string &name)
{
    Channel *channel;

    if (!client)
        return ;
    if (!channelExists(name))
        return;

    channel = getChannel(name);

    if (!channel->hasMember(client))
        return;

    channel->removeMember(client);
    client->removeChannel(name);

    if (channel->isEmpty())
    {
        delete channel;
        _channels.erase(name);
    }
}

Client *Server::getClientByNick(const std::string &nickname)
{
    std::map<int, Client*>::iterator it;

    it = _clients.begin();
    while (it != _clients.end())
    {
        if (it->second->getNickname() == nickname)
            return (it->second);
        it++;
    }
    return (NULL);
}

void Server::sendToClient(Client *target, std::string message)
{
    if (!target)
        return;
    message.append("\r\n");
    std::cout << "> " << message << std::endl;
    send(target->getFd(), message.c_str(), message.length(), 0);
}

void Server::sendToChannel(Channel &channel, Client *sender, std::string message)
{
    std::set<Client*>::const_iterator it;
    const std::set<Client*> &members = channel.getMembers();

    message.append("\r\n");
    std::cout << "> " << message << std::endl;
    it = members.begin();
    while (it != members.end())
    {
        if (*it != sender)
            sendToClient((*it), message);
        it++;
    }
}

void Server::sendMessageToClient(Client *sender, Client *target, const std::string &message)
{
    std::string msg = sender->getNickname() + " PRIVMSG :" + message; 
    sendToClient(target, msg);
}

void Server::sendMessageToChannel(Client &sender, Channel &channel, const std::string &message)
{
    std::string msg = sender.getNickname() + " PRIVMSG :" + message;
    sendToChannel(channel, &sender, msg);
}

void Server::sendJoinConfirmation(Client *client, Channel &channel)
{
    std::string confirmation = ":" + client->getNickname() + " JOIN :" + channel.getName();
    sendToClient(client, confirmation);
    if (channel.hasTopic())
        sendToClient(client, RPL_TOPIC(channel.getName(), channel.getTopic()));
    else
        sendToClient(client, RPL_NOTOPIC(channel.getName()));
    sendToClient(client, RPL_NAMREPLY(client->getNickname(), channel.getName(), channel.listAllUsers(client->getNickname())));
    sendToClient(client, RPL_ENDOFNAMES(client->getNickname(), channel.getName()));
}

void Server::sendPartConfirmation(Client *client, Channel &channel) // BESOIN?
{
    std::string confirmation = ":" + client->getNickname() + " PART :" + channel.getName();
    sendToClient(client, confirmation);
    sendToChannel(channel, client, confirmation);
    //sendToClient(client, RPL_NAMREPLY(channel.getName(), channel.listAllUsers(client->getNickname())));
    //sendToClient(client, RPL_ENDOFNAMES(client->getNickname(), channel.getName()));
}

void Server::sendNewParams(Channel &channel, Client *sender, std::string flag)
{
    //Parameters: <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>] [<ban mask>]

    (void)flag;
    std::string mode;
    std::string params;
    sendToClient(sender, RPL_CHANNELMODEIS(channel.getName(), mode, params));
    sendToChannel(channel, sender, RPL_CHANNELMODEIS(channel.getName(), mode, params));
}

void Server::sendCap(Client *client)
{
    std::string cap = "CAP * LS :" + _name;
    sendToClient(client, cap);
}

void Server::pong(Client *client, std::string arg)
{
    std::string pong = "PONG " + arg;
    sendToClient(client, pong);
}