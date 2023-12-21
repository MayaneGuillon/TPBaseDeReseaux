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
    // /////////////////////////// GET TFTP ////////////////////////////////////
    /*
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

    // used BlockSize Q6 (needed to not have too much request with the time of write function)
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
     */
    // /////////////////////////// PUT TFTP ////////////////////////////////////
    // Q1 : puttftp
    /*if (argc!=4){
        printf("Wrong usage : puttftp filename host port\n");
        exit(EXIT_SUCCESS);
    }
    // alt256 srvtinfo1.ensea.fr 69
    const char * filename2=argv[1];
    const char * host=argv[2];
    const char * port=argv[3];
    printf("puttftp Server : Filename : %s , Host : %s , Port : %s \n", filename2, host, port);*/
    //Q5
    open("bonjour.txt", O_WRONLY, S_IRWXG|S_IRWXU|S_IRWXO);
    const char * filename="bonjour.txt";
    const char * host=argv[2];
    const char * port=argv[3];printf("puttftp Server : Filename : %s , Host : %s , Port : %s \n", filename, host, port);
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

    char wrq[MAX_SIZE_BUFFER]={0};
    // //////////////////////////////// The  Only change /////////////////////////////////////////////////////////
    sprintf(wrq," \2%s octet",argv[1]); // not 01 as rrq but 02 for wrq
    // ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    // wrq
    wrq[0]=0;
    wrq[strlen(argv[1])+2]=0;
    int sock = socket(result -> ai_family, result -> ai_socktype, result -> ai_protocol);

    int read=read("bonjour.txt", wrq, MAX_SIZE_BUFFER);

    ssize_t send = sendto(sock, wrq, strlen(argv[1]) + 9, 0, result->ai_addr, result->ai_addrlen);
    if (send == -1) {
        printf("Erreur de l'envoi de la demande");
        exit(EXIT_FAILURE);
    }
    //data
    char returnData[4] = {0};
    struct sockaddr receivedSocket;
    int receivedSocketSize;
    int recv = recvfrom(sock, returnData, 4, 0, &receivedSocket, &receivedSocketSize);
    printf("Received %d bytes for DATA, block number .\n", recv);
    if (returnData[0]==0|returnData[1]==4|returnData[2]==0|returnData[3]==1){
        char data[MAX_SIZE_BUFFER] = {0}; //MAX_SIZE_BUFFER=1024
        struct sockaddr SendSocket;
        int SendSocketSize;
        ssize_t sendData = sendto(sock, data, MAX_SIZE_BUFFER, 0, &SendSocket, SendSocketSize);
    }
    return 0;
}