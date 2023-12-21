#include "tftp.h"

/*

int main(int argc, char *argv[]){

    //argv[1] host
    //argv[2] port
    //argv[3] file name

    // Check for the correct number of arguments
    if(argc != 4){
        printf("There are %d arguments instead of 3\n", argc);
        return(EXIT_FAILURE);
    }
    printf("Sending %s to host: %s@%s\n", argv[3], argv[1], argv[2]);

    struct addrinfo hints;
    struct addrinfo *res;

    memset(&hints, 0, sizeof(struct addrinfo)); //sets to 0 our struct addrinfo
    hints.ai_family = AF_INET; // Specify IPv4
    hints.ai_protocol = IPPROTO_UDP; // Use UDP protocol
    int status;
    status = getaddrinfo(argv[1], argv[2], &hints, &res);
    // Check the result of getaddrinfo
    if (status == -1){
        printf("Cannot find host %s\n", argv[1]);
        return(EXIT_FAILURE);
    }

    char buffer[MAXSIZE] = {0};
    char buffer_receive[MAXSIZE] = {0};
    buffer[1] = 1; // Setting the operation code
    sprintf(buffer + 2, "%s", argv[3]); // Appends the file name
    sprintf(buffer + 3 + strlen(argv[3]), "NETASCII"); // Appends the mode

    int sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    // Check if socket was successfully created
    if (sock == -1){
        printf("Error in socket creation.\n");
        return EXIT_FAILURE;
    }
    int bufferSize = 12 + strlen(argv[3]);

    int send = sendto(sock, buffer, bufferSize, 0, res->ai_addr, res->ai_addrlen);
    // Check if sending the request was successful
    if (send == -1){
        printf("Error in sending the request.\n");
        return EXIT_FAILURE;
    }
    // Request has been sent

    struct sockaddr adresse;
    socklen_t sizeAdress = sizeof(adresse);
    int nbByte;

    FILE *file;
    struct stat info;
    if(stat(argv[3], &info) != 0) {
        file = fopen(argv[3], "w");
        // Check if file is successfully opened for writing
        if (!file) {
            printf("Error in opening file for writing.\n");
            return EXIT_FAILURE;
        }
    }
    else {
        printf("File already exists\n");
        return EXIT_SUCCESS;
    }
    int block = 1;
    char buff_ok[MAXSIZE] = {0};
    int send2;

    while (1) {
        nbByte = recvfrom(sock, buffer_receive, MAXSIZE, 0, &adresse, &sizeAdress);
        // Check if receiving data was successful
        if (nbByte == -1){
            printf("Error in receiving data.\n");
            fclose(file);
            return EXIT_FAILURE;
        }
        // Exit loop if no more data is received
        if (nbByte < 512) {
            break;
        }

        printf("Just received %d bytes\n", nbByte); // Reception successful

        if (buffer_receive[0] == 0 && buffer_receive[1] == 5){
            printf("Error received from server, during block #%d:\n%s\n", buffer_receive[3], buffer_receive + 4);
            fclose(file);
            exit(EXIT_SUCCESS);
        }
        if (buffer_receive[0] == 0 && buffer_receive[1] == 3){
            buff_ok[1] = 4; // Acknowledgment operation code
            buff_ok[2] = 0;
            buff_ok[3] = block;
            block++;
            send2 = sendto(sock, buff_ok, 4, 0, &adresse, sizeAdress); // Send acknowledgment
            // Check if sending acknowledgment was successful
            if (send2 == -1){
                printf("Error in sending acknowledgment.\n");
                fclose(file);
                return EXIT_FAILURE;
            }
        }

        // Writes our received file
        fwrite(buffer_receive + 4, sizeof(char), nbByte - 4, file);
        // Checks if fwrite was successful
        if (ferror(file)) {
            printf("Error in writing to file.\n");
            fclose(file);
            return EXIT_FAILURE;
        }
    }

    fclose(file);

    return 0;
}


*/




