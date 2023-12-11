#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#define MAXSIZE 500



int main (int argc, char * argv[]){
    // Socket file descriptor and buffer arrays for host and service names
    int sfd;
    char bufferHostName[MAXSIZE];
    char bufferServiceName[MAXSIZE];


    // Structs for storing address information
    struct addrinfo hints;
    struct addrinfo *result;


    // Verify the correct number of arguments are passed
    if(argc < 3){
        printf("\nInsufficient arguments. gettftp.c uses 3 (You must specify the server then the file).\n");
        exit(EXIT_FAILURE);
    }


    // Initialize hints structure to zero for safety
    memset(&hints, 0, sizeof(hints));


    // Allow for either IPv4 or IPv6
    hints.ai_family = AF_UNSPEC;
    // Datagram socket for UDP connection
    hints.ai_socktype = SOCK_DGRAM;
    // No flags specified
    hints.ai_flags = 0;
    // Any protocol
    hints.ai_protocol = 0;


    // Call getaddrinfo() and check for errors
    int test = getaddrinfo(argv[1],argv[2],&hints,&result);
    if (test != 0){
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(test));
        exit(EXIT_FAILURE);
    }


    // Retrieve the name information for the server's address
    getaddrinfo(argv[1], argv[2], &hints, &result);
    getnameinfo(result->ai_addr, result->ai_addrlen, bufferHostName, MAXSIZE, bufferServiceName, MAXSIZE, NI_DGRAM);


    // Print the server's host and service names
    printf("Server : %s:%s\n",bufferHostName, bufferServiceName);


    exit(EXIT_SUCCESS);
}
