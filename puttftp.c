#include "tftp.h"


int put(const char* host, const char* port, const char* fileName) {
    int sockfd;
    struct addrinfo hints, *serverinfo, *p;
    int rv;
    char buffer[BUFFER_SIZE];

    // Create socket
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_DGRAM;

    if ((rv = getaddrinfo(host, port, &hints, &serverinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }

    // loop through all the results and make a socket
    for(p = serverinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }
        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to create socket\n");
        return 2;
    }

    // Create and send WRQ
    // Variables for WRQ packet
    const char *mode = "octet";
    int wrq_packet_size = 2 + strlen(fileName) + 1 + strlen(mode) + 1;
    char wrq_packet[wrq_packet_size];

    // Fill the WRQ packet
    wrq_packet[0] = 0; // First byte of opcode
    wrq_packet[1] = 2; // Second byte of opcode (2 for WRQ)
    strcpy(&wrq_packet[2], fileName); // Copying filename
    strcpy(&wrq_packet[2 + strlen(fileName) + 1], mode); // Copying mode

    // Send WRQ packet
    if (sendto(sockfd, wrq_packet, wrq_packet_size, 0, p->ai_addr, p->ai_addrlen) == -1) {
        perror("sendto: WRQ");
        close(sockfd);
        return 3;
    }


    freeaddrinfo(serverinfo); // free the linked-list

    close(sockfd);
    return 0;
}

int main(int argc, char *argv[]){
    put("localhost","1069","non");
}
