#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/un.h>

#define PORT 8000
#define MAXLINE 20 

int main()
{
    int sockfd; 
    int len;
    char buffer[MAXLINE]; 
    struct sockaddr_un server, client;

    strcpy(buffer, "Hello, 1!");

    if((sockfd = socket(AF_LOCAL, SOCK_STREAM, 0)) < 0){
        perror(NULL);
        close(sockfd);
        exit(1);
    }

    server.sun_family = AF_LOCAL;
    strcpy(server.sun_path, "/tmp/stream_serv");

    if (connect(sockfd, (struct sockaddr*)&server, sizeof(server)) < 0) {
		printf("could not connect to server\n");
		return 1;
	}

    if((len = send(sockfd, (char *)buffer, MAXLINE, 0)) < 0)
    {
        perror(NULL);
        close(sockfd);
        exit(1);
    }

    if((len = recv(sockfd, (char *)buffer, MAXLINE, 0)) < 0)
    {
        perror(NULL);
        close(sockfd);
        exit(1);
    }

    buffer[len] = '\0'; 
    printf("Server: %s\n", buffer);

    return 0;
}