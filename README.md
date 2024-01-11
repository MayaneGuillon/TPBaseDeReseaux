# TP de Synthèse – Client TFTP

**Mayane GUILLON et Rania DOUIA**

## Question 1 : Optimisation des Requêtes TFTP avec gettftp et puttftp
*Objectif: vérifier la validité des arguments de ligne de commande pour les clients gettftp et puttftp et afficher les informations associées en cas de saisie correcte.*

Le code écrit gère deux clients en ligne de commande, gettftp et puttftp, pour le transfert de fichiers via le protocole TFTP. 

Il vérifie simplement si le nombre d'arguments est correct (4 : alt256 srvtinfo1.ensea.fr 69), affichant un message d'erreur sinon. 

S'il est correct, il extrait et affiche les informations nécessaires (nom de fichier, hôte, port) pour vérification. 

![Q](img/Q1Terminal.png)


## Question 2 : Utilisation de la fonction getaddrinfo
*Objectif: préparer la connexion au serveur TFTP en résolvant l'adresse à partir du nom d'hôte et du numéro de port, en utilisant la fonction getaddrinfo.*

Cette question concerne la résolution de l'adresse du serveur à partir du nom d'hôte et du numéro de port fournis en ligne de commande. 

Pour ce faire, le programme utilise la fonction getaddrinfo, qui prend en compte des informations spécifiques sur la configuration du socket à travers la structure hints. 

Cette fonction permet de préparer une structure d'informations sur l'adresse du serveur, qui sera utilisée ultérieurement pour établir une connexion avec le serveur TFTP.

Plus précisémment, le code initialise la structure hints avec des paramètres tels que la famille d'adresses (IPv4 dans ce cas), le type de socket, et le protocole à utiliser. 

Ensuite, la fonction getaddrinfo est appelée avec le nom d'hôte ("host") et le numéro de port. Si la résolution de l'adresse est réussie, les informations sont stockées dans la structure result.

Cette partie du code s'occupe de la préparation des informations nécessaires pour établir une connexion avec le serveur TFTP, en convertissant le nom d'hôte en une adresse IP utilisable.

## Question 3 et 4 : Transfert de fichier depuis le serveur
*Objectif: implémenter le transfert de fichiers depuis le serveur TFTP vers le client (gettftp):
(3) Réservation d'un socket de connexion vers le serveur.
(4a)Construction d'une requête en lecture (RRQ) correctement formée et envoi au serveur.
(4b) Réception d'un fichier constitué d'un seul paquet de données (DAT) et son acquittement (ACK).
(4c) Réception d'un fichier constitué de plusieurs paquets de données (DAT) et de leurs acquittements respectifs (ACK).*


Pour cette question, on implémente un client TFTP (gettftp) qui utilise le protocole TFTP pour télécharger un fichier depuis un serveur TFTP distant.

* **Initialisation et Résolution d'Adresse :**

Le programme commence par vérifier la validité des arguments de ligne de commande.

Il résout l'adresse du serveur à l'aide de la fonction getaddrinfo, comme expliqué précédemment.

* **Construction et Envoi de la Requête RRQ :**

Une fois l'adresse du serveur résolue, le programme construit une requête de lecture (Read Request - RRQ) en utilisant le nom du fichier passé en ligne de commande.

Un socket est créé pour la communication avec le serveur.

La requête RRQ est envoyée au serveur à l'aide de la fonction sendto.

* **Réception et Traitement des Paquets de Données :**

Le programme entre ensuite dans une boucle où il attend de recevoir des paquets de données du serveur à l'aide de la fonction recvfrom.

Chaque paquet de données reçu est traité. Les données utiles (le contenu du fichier) sont extraites du paquet et écrites dans un fichier local sur le client.

**Format des donnée (valeurs du opcode):**

![Q](img/FormatData.png) 
![Q](img/Q4Opcode.png)

Un accusé de réception (ACK) est envoyé au serveur pour confirmer la réception du paquet de données.

**Format du ACK :**

![Q](img/formatACK.png)

* **Gestion des Paquets de Données Multiples :**

Si le fichier à télécharger nécessite plusieurs paquets, le programme répète le processus de réception et d'accusé de réception jusqu'à ce que tous les paquets soient reçus.

La boucle continue jusqu'à ce qu'un paquet de données reçu soit de taille inférieure à la taille maximale autorisée (516 octets), indiquant la fin du transfert.

* **Fermeture du Fichier et du Socket :**

Une fois tous les paquets de données reçus et écrits dans le fichier local, le fichier est fermé.

Le socket est également fermé, et le programme se termine.



En résumé, ces questions illustrent les étapes du protocole TFTP pour établir une connexion avec le serveur, envoyer une requête de lecture, recevoir et écrire les données dans un fichier local, et confirmer la réception de chaque paquet de données.

**Valeur de rrq et data déterminées avec le debugger:**

A l'aide du degugger, on retrouve bien que l'on a :  

* **rrq** avec son opcode '01' , puis le nom du fichier 'alt256'.

![Q](img/Q4DebugRrq.png)

* **data** avec son opcode '03' , puis on a '01' pour determiner de block, et enfin l'ensemble des données sur 516octets.

![Q](img/Q4DebugData.png)


**Liste des fichiers créés par la suite (requête dans le terminal):** 

![Q](img/Q4terminal2.png)

**Retour dans la console :** *alt256*

![Q](img/Q4TerminalAlt256.png)

Pour récupérer le fichier 'alt256' (qui alterne 8 zéros puis 8 uns), on récupère un block de 260octets ce qui correspond bien aux 256o donné par le terminal sur l'image précédente. 

**Contenu du fichier :** *alt256*

![Q](img/Q4terminal.png) 

**Retour dans la console :** *alt256*

![Q](img/Q4TerminalOnes1024.png)

Pour récupérer le fichier 'ones1024' ( grand fichier contenant que des uns), on récupère 2 blocks de 516octets et un de 4octets ce qui correspond bien aux 1ko donné par le terminal sur l'image précédente. 


**Retour dans la console :** *ensea.png* 

![Q](img/Q4TerminalEnseapng1.png)
![Q](img/Q4TerminalEnseapng2.png)

Pour récupérer le logo de l'ensea 'ensea.png', on recupère 41 blocks de donnée de 516 octets et un de 430 octets ce qui correspond bien au 21ko du fichier image.


On voit bien que le fichier alt256 a été créée et que l'on a récupérer l'image ensea.png.

![Q](img/Q4Architecteture.png)

## Question 5 : Transfert de fichier vers le serveur
*Objectif:  implémenter le transfert de fichiers du client vers le serveur (puttftp):
(5a) Construction d'une requête en écriture (WRQ) correctement formée et envoi au serveur ; 
(5b) Envoi d'un fichier constitué d'un seul paquet de données (DAT) et réception de son acquittement (ACK) ; 
(5c) Envoi d'un fichier constitué de plusieurs paquets de données (DAT) et réception de leurs acquittements respectifs (ACK)*

Notre tentative d'implémentation du transfert de fichiers du client vers le serveur (puttftp) en utilisant le protocole TFTP :

* **Construction et Envoi de la Requête WRQ :**

Une requête en écriture (Write Request - WRQ) est construite avec le nom du fichier à écrire sur le serveur. L'opcode 02 est utilisé pour indiquer qu'il s'agit d'une requête d'écriture.

La requête WRQ est envoyée au serveur via la fonction sendto.

* **Réception de l'Acquittement Initial :**

Le client attend de recevoir un acquittement (ACK) initial du serveur.

* **Envoi de Paquets de Données (DAT) :**

Après avoir reçu l'ACK initial, le client commence à envoyer des paquets de données au serveur. Cependant, l'opcode de retour renvoit un code d'erreur, il semble y avoir une erreur dans notre code.

![Q](img/Q5err.png)




## Réflexions personnelles
### Mayane GUILLON

La réalisation de ce TP sur le protocole TFTP a été une expérience formatrice. En implémentant les clients gettftp et puttftp, j'ai appliqué les concepts théoriques de programmation réseau. La résolution d'adresses, la construction des requêtes, et la gestion des paquets m'ont permis de renforcer mes compétences en développement logiciel.

Ce TP a souligné l'importance de la précision dans la conformité aux spécifications du protocole. Les erreurs d'opcode et les défis de communication client-serveur ont renforcé ma capacité à débugger et à résoudre des problèmes complexes. En conclusion, cette expérience a enrichi ma compréhension pratique du développement d'applications réseau, renforçant mes compétences techniques et ma confiance dans la programmation orientée réseau.


### Rania DAOUIA 

Ce TP sur le protocole TFTP a été une expérience enrichissante qui a considérablement contribué à ma progression en programmation réseau. En développant les clients gettftp et puttftp, j'ai acquis une compréhension approfondie du fonctionnement du protocole, de la validation des arguments de ligne de commande à la résolution d'adresse et à la gestion des paquets de données. Les défis rencontrés, notamment lors de la tentative d'implémentation du client puttftp, ont renforcé mes compétences de débogage et m'ont appris l'importance de la précision dans la programmation conformément aux spécifications du protocol.
