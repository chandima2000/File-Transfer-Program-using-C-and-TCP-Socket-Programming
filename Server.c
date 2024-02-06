#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Port number is not provided\n");
        exit(1);
    }

    int sockfd, newsockfd, portno, n;
    char buffer[256];

    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("Error opening Socket");
    }

    bzero((char *)&serv_addr, sizeof(serv_addr));

    portno = atoi(argv[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        error("Binding Failed.");
    }

    listen(sockfd, 5);

    clilen = sizeof(cli_addr);

    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);

    if (newsockfd < 0) {
        error("Error on Accept");
    }

    FILE *fp;
    int ch = 0;
    int words;

    read(newsockfd, &words, sizeof(int));

    fp = fopen("Greet_received.txt", "a");

    while (ch != words) {
        read(newsockfd, buffer, sizeof(buffer));
        fprintf(fp, "%s ", buffer);
        ch++;
    }

    printf("The file has been received successfully. It is saved by the name Greet_received.txt\n");

    close(newsockfd);
    close(sockfd);
    fclose(fp);
    return 0;
}
