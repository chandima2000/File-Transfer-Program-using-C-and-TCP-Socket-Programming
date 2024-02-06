#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <ctype.h>

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <filename> <server-IP-address> <port>\n", argv[0]);
        exit(1);
    }

    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];

    portno = atoi(argv[3]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        error("ERROR opening socket");
    }

    server = gethostbyname(argv[2]);
    if (server == NULL) {
        fprintf(stderr, "Error, no such host");
        exit(0);
    }

    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        error("Connection Failed");
    }

    FILE *f;
    int words = 0;
    char c;

    f = fopen(argv[1], "r");
    if (f == NULL) {
        error("Error opening file");
    }

    while ((c = getc(f)) != EOF) {
        if (isspace(c) || c == '\t') {
            words++;
        }
    }

    rewind(f);
    write(sockfd, &words, sizeof(int));

    while (fscanf(f, "%s", buffer) == 1) {
        write(sockfd, buffer, sizeof(buffer));
    }

    printf("The file has been successfully sent.\n");

    close(sockfd);
    fclose(f);
    return 0;
}
