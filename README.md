*This project has been created as part of the 42 curriculum by mrosset, llabatut, cyglardo.*

# POUR LE GROUPE

## Etapes
?

## D'ICI PROCHAINE REU
- M, L & C: dégrossir le projet (lire le sujet, se faire une première idée de ce qui est demandé)

## A FAIRE
- identifier les nouveautés et commencer à se renseigner sur celles-ci
- identifer des étapes à suivre
- distribuer les tâches

## Utilisation du git
- Chacune crée sa propre branche et travaille exclusivement sur la sienne.
- Chacune push régulièrement (à chaque modification importante) sur sa propre branche.
- Chacune prend le réflexe de faire un git pull à chaque fois qu'elle réouvre le projet, pour s'assurer d'être à jour avant de commencer à faire des modifications.
- Quand on estime avoir terminé sur sa branche, on notifie les autres de sa volonté de merge: le merge n'est fait que lorsque tout le monde a donné le feu vert.
- Quand il y a eu merge, chacune s'assure que sa branche repart sur la même base commune (quitte à en recréer une et supprimer l'ancienne).
- Dans la mesure du possible, on ne merge que des versions stables.

### Créer sa propre branche
Dans VSCode, cliquez sur le nom de la branche actuelle (de base: main) en bas à gauche.

<img width="219" height="43" alt="github_branche" src="https://github.com/user-attachments/assets/60b117ac-e4ba-4c3d-987c-21ce724ec715" />

Cela ouvrira un menu dans la palette de commandes. Sélectionnez "Create new branch"

<img width="611" height="212" alt="github_newbranche" src="https://github.com/user-attachments/assets/d905c167-c8d1-451e-82eb-d699df5dac68" />

Entrez un nom pour la branche. Idéalement, le nom doit refléter la feature que vous comptez implémenter (par ex.: "parsing"). Appuyez sur ``enter``.
Si tout a fonctionné, le nom de la branche actuelle, en bas à gauche de votre fenêtre VSCode, doit être celui que vous venez d'entrer.

### Push sa branche
Quand vous tenterez de push sur votre nouvelle branche pour la première fois, VSCode vous demandera d'utiliser une commande spécifique à la place de juste ``push``: copiez-collez celle qu'il vous donne et appuyez sur ``enter``. Ex:
```git push --set-upstream origin parsing```

Pour les fois suivantes, vous pourrez utiliser la simple commande ``push`` comme d'habitude.

### Merge sa branche
Allez sur la page web du github. Si vous avez push quelque chose, vous devriez en avoir la notification au sommet de la page, et un nouveau bouton vert "Compare & pull request" est accessible: cliquez dessus.

<img width="928" height="134" alt="github_compare" src="https://github.com/user-attachments/assets/6d1348fa-6f57-4829-aa98-0441a13f49bd" />

Si vous ne voyez pas cette notification, vous pouvez accéder au même bouton en accédant à la page de votre branche, puis en cliquant sur l'hypertexte "is x commits ahead of main", puis sur le bouton "Create pull request":

<img width="345" height="313" alt="github_brancheselection" src="https://github.com/user-attachments/assets/587729f0-b426-463f-aa96-e28190fab444" />

<img width="916" height="109" alt="github_aheadof" src="https://github.com/user-attachments/assets/12904222-965f-4e81-9d0d-79d132d4c9b8" />

<img width="1243" height="223" alt="github_createpullrequest" src="https://github.com/user-attachments/assets/518bad28-bb80-4011-a9fd-3110e9f228dc" />

Peu importe par où vous êtes passé-e, vous voilà désormais sur la page de votre requête de merge. Depuis là, vous pouvez entrer des détails comme un titre et une description, et lire les commentaires de vos collègues sur votre requête. Mais surtout, vous pouvez, si aucun conflit n'est détecté, appuyer sur le bouton vert "Merge pull request".

<img width="908" height="197" alt="github_noconflict" src="https://github.com/user-attachments/assets/2a8198c4-73dd-4de0-94b1-0aed32ae0cd0" />

Vous devrez encore appuyer sur "confirmer" avant que le merge soit effectif.

Une fois cela fait, bravo! Vous avez merge votre branche et pouvez la supprimer.

Si des conflits sont détectés, vous ne pourrez pas merge aussi facilement: cliquez sur "resolve conflicts" et retirez le code fautif; une fois un fichier corrigé, marquez-le comme résolu. Si tous les conflits sont corrigés, vous pourrez accéder au bouton "Merge pull request".

### Supprimer sa branche
Retournez sur la page d'accueil du github. Cliquez sur la liste des branches, puis sur le symbole "poubelle" de la vôtre.

<img width="318" height="49" alt="github_allbranches" src="https://github.com/user-attachments/assets/ba4fa634-83e4-404e-8427-5b98e98e3f52" />

<img width="1307" height="134" alt="github_branchdelete" src="https://github.com/user-attachments/assets/94246f61-c791-4aa6-bbb4-c98491c70ce5" />



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

Press ``enter``. If everything worked, a new file should have been created, named "ft_irc". Execute it with a port and password (given in the "configuration.txt" file), like this:
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
