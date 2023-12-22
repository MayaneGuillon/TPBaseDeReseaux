# TP de Synthèse – Client TFTP

**Mayane GUILLON et Rania DOUIA**

## Question 1 : Optimisation des Requêtes TFTP avec gettftp et puttftp
*Objectif: vérifier la validité des arguments de ligne de commande pour les clients gettftp et puttftp et afficher les informations associées en cas de saisie correcte.*

Le code écrit gère deux clients en ligne de commande, gettftp et puttftp, pour le transfert de fichiers via le protocole TFTP. 

Il vérifie simplement si le nombre d'arguments est correct (4 : alt256 srvtinfo1.ensea.fr 69), affichant un message d'erreur sinon. 

S'il est correct, il extrait et affiche les informations nécessaires (nom de fichier, hôte, port) pour vérification. 

![Q](img/Q1Terminal.png)


## Question 2 :
*Objectif: préparer la connexion au serveur TFTP en résolvant l'adresse à partir du nom d'hôte et du numéro de port, en utilisant la fonction getaddrinfo.*

Cette question concerne la résolution de l'adresse du serveur à partir du nom d'hôte et du numéro de port fournis en ligne de commande. 

Pour ce faire, le programme utilise la fonction getaddrinfo, qui prend en compte des informations spécifiques sur la configuration du socket à travers la structure hints. 

Cette fonction permet de préparer une structure d'informations sur l'adresse du serveur, qui sera utilisée ultérieurement pour établir une connexion avec le serveur TFTP.

Plus précisémment, le code initialise la structure hints avec des paramètres tels que la famille d'adresses (IPv4 dans ce cas), le type de socket, et le protocole à utiliser. 

Ensuite, la fonction getaddrinfo est appelée avec le "host" et le numéro de port. Si la résolution de l'adresse est réussie, les informations sont stockées dans la structure result.

Cette partie du code s'occupe de la préparation des informations nécessaires pour établir une connexion avec le serveur TFTP, en convertissant le nom d'hôte en une adresse IP utilisable.

## Question 3 :
*Objectif:*


## Question 4 : 
*Objectif:*

![Q](img/Q4Architecture.png)
![Q](img/Q4DebugData.png)
![Q](img/Q4DebugRrq.png)
![Q](img/Q4TerminalAlt256.png)
![Q](img/Q4TerminalEnseapng1.png)
![Q](img/Q4TerminalEnseapng2.png)
![Q](img/Q4TerminalOnes1024.png)
![Q](img/Q4terminal.png)
![Q](img/Q4terminal2.png)
![Q](img/FormatData.png)
![Q](img/formatACK.png)

## Question 5 : 
*Objectif:*



## Question 6 : 
*Objectif:*







## Réflexions personnelles
### Mayane GUILLON



### Rania DAOUIA 

