#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define MAX_SIZE_BUFFER 1024

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
    //Q3 et Q4
    char rrq[MAX_SIZE_BUFFER]={0};
    sprintf(rrq," \1%s octet",argv[1]);
    rrq[0]=0;
    rrq[strlen(argv[1])+2]=0;

    int sock = socket(result -> ai_family, result -> ai_socktype, result -> ai_protocol);
    //sendto() is to send data on a socket
    //we want to load this data in a file (on memory)
    int file=open(filename, O_CREAT|O_WRONLY|O_TRUNC, S_IRWXG|S_IRWXU|S_IRWXO);
    //00700 user (file owner) has read, write, and execute permission
    //00070 group has read, write, and execute permission
    //00007 others have read, write, and execute permission
    //   Even we can use creat() function: A call to creat() is equivalent to calling open() with flags equal to O_CREAT|O_WRONLY|O_TRUNC.



    ssize_t send = sendto(sock, rrq, strlen(argv[1]) + 9, 0, result->ai_addr, result->ai_addrlen);

    if (send == -1) {
        printf("Erreur de l'envoi de la demande");
        exit(EXIT_FAILURE);
    }
    ssize_t recv;
    int blockNumber=1;
    int blockReceived=0;
    do {
        char data[MAX_SIZE_BUFFER] = {0}; //MAX_SIZE_BUFFER=1024
        struct sockaddr receivedSocket;
        int receivedSocketSize;
        recv = recvfrom(sock, data, 1024, 0, &receivedSocket, &receivedSocketSize);
        blockReceived=data[2]*256+data[3];
        printf("Received %d bytes for DATA, block number %d.\n", recv,blockReceived);
        if(blockReceived==blockNumber){
            write(file, data + 4, recv - 4);
            blockNumber++;
        }
        char ack[4] = {0, 4, 0, 0}; //04 : Acknowledgment opcode
        ack[2] = data[2];
        ack[3] = data[3];
        int lenACK = 4;
        ssize_t sendACK = sendto(sock, ack, lenACK, 0, &receivedSocket, receivedSocketSize);
    }while(recv==516);
    close(file);
    return 0;
}
