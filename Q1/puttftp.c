#include <stdio.h>
#include <stdlib.h>

int main (int argc, char ** argv){
    // Q1 : puttftp
    if (argc!=4){
        printf("Wrong usage : puttftp filename host port\n");
        exit(EXIT_SUCCESS);
    }
    // alt256 srvtinfo1.ensea.fr 69
    const char * filename=argv[1];
    const char * host=argv[2];
    const char * port=argv[3];
    printf("puttftp Server : Filename : %s , Host : %s , Port : %s \n", filename, host, port);
    return 0;
}