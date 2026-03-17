*This project has been created as part of the 42 curriculum by mrosset, llabatut, cyglardo.*

# Description
The ft_irc projects consists of creating a server that can be used by an IRC client.

Basically, the task is to develop a programm that allows to exchange public and private messages by creating and managing accounts and channels on an already existing IRC client, using the TCP/IP protocol to communicate with it.

Several things are needed in order to accomplish this:
- Understanding how to use the TCP/IP protocol, more precisely how to manage the packets.
- Understanding how to use sockets.
- Understanding how to manage accounts and authentication.
- Parsing the commands.

# Instructions
Copy the link of the repository. You can find it by clicking on the green button labelled "<>Code" at the top of the page.

In your terminal, choose the location where you want to install ft_irc, then type:
````
git clone pasteTheLinkYouCopied
````
Paste the link and press ``enter``.

In your terminal, go in the cloned repository and type:
````
make
````

Press ``enter``. If everything worked, a new file should have been created, named "ft_irc". Execute it with a port and password (example given in the "configuration.txt" file), like this:
````
./ft_irc port password
````

Press ``enter``. The server should now be running. Open the IRC client and connect it to your server using its name, its port and its password.
https://docs.redhat.com/en/documentation/red_hat_fuse/7.3/html/connecting_fuse_online_to_applications_and_services/connecting-to-irc_connectors

If the connection is successful, you can now use the client as if it was connected to any official server. 

To test it thoroughly, open multiple clients and connect them all to the server. Every client should work normally and act as different users.

## Things you can try:
- authenticate
- set a nickname
- set a username
- join a channel
- write a private message to an other user (client)
- kick a user (client) from a channel
- invite a user (client) to a channel
- change and view the channel topic
- change the channel's parameters (mode):
  * set / remove the access to the channel (open / invite only)
  * set / remove the restrictions on the command allowing to change or view the channel topic
  * set / remove the channel's password (key)
  * give / take owner (operator) privilege
  * set / remove user limit

# Ressources
Several websites were used to understand the different technical aspects of the project.

General informations:
- https://medium.com/@mohcin.ghalmi/irc-server-internet-relay-chat-bd08e4f469f8
- https://www.geeksforgeeks.org/operating-systems/i-o-scheduling-in-operating-systems/

The poll() function:
- https://man7.org/linux/man-pages/man2/poll.2.html
- https://www.ibm.com/docs/en/i/7.4.0?topic=ssw_ibm_i_74/apis/poll.htm

Choosing an IRC client:
- https://libera.chat/guides/clients

Understanding how the IRC client works:
- https://docs.redhat.com/en/documentation/red_hat_fuse/7.3/html/connecting_fuse_online_to_applications_and_services/connecting-to-irc_connectors

Understanding the sockets:
- https://www.geeksforgeeks.org/c/socket-programming-cc/

Understanding the packets:
- https://dev.to/3rev/demystifying-tcpip-understanding-the-journey-of-a-network-packet-38g7
