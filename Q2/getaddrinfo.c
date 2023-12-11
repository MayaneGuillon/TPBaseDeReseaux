#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>

int main (int argc, char ** argv){
    // gettftp
    if (argc!=4){
        printf("Wrong usage : gettftp filename host port\n");
        exit(EXIT_SUCCESS);
    }
    // alt256 srvtinfo1.ensea.fr 69
    const char * filename=argv[1];
    const char * host=argv[2];
    const char * port=argv[3];
    printf("gettftp Server : Filename : %s , Host : %s , Port : %s \n", filename, host, port);

    struct addrinfo * result;
    struct addrinfo hints;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family=AF_INET;
    hints.ai_socktype=SOCK_DGRAM;
    hints.ai_protocol=IPPROTO_UDP;

    getaddrinfo(argv[2], argv[3], &hints, &result);

}