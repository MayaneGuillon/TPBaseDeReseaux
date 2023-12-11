#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

#define MAX_SIZE_BUFFER 128

int main (int argc, char ** argv){
    // Q1 : gettftp
    if (argc!=4){
        printf("Wrong usage : gettftp filename host port\n");
        exit(EXIT_SUCCESS);
    }
    // alt256 srvtinfo1.ensea.fr 69
    const char * filename=argv[1];
    const char * host=argv[2];
    const char * port=argv[3];
    printf("gettftp Server : Filename : %s , Host : %s , Port : %s \n", filename, host, port);

    //Q2
    struct addrinfo * result;
    struct addrinfo hints;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family=AF_INET;
    hints.ai_socktype=SOCK_DGRAM;
    hints.ai_protocol=IPPROTO_UDP;

    int status = getaddrinfo(argv[2], argv[3], &hints, &result);
    if (status !=0){
        printf("we can't find the host %s", argv[2]);
        exit(EXIT_FAILURE);
    }
    //Q3
    char rrq[MAX_SIZE_BUFFER]={0};
    sprintf(rrq," \1 %s octets",argv[1]);
    rrq[0]=0;
    rrq[strlen(argv[1])+2]=0;

    int sock = socket(result -> ai_family, result -> ai_socktype, result -> ai_protocol);
    //sendto() is to send data on a socket
    ssize_t send=sendto(sock, rrq, sizeof(rrq) , 0, result ->ai_addr, result->ai_addrlen);
    if (send ==-1){
        printf("Erreur de l'envoi de la demande");
        exit(EXIT_FAILURE);
    }
    return 0;
}