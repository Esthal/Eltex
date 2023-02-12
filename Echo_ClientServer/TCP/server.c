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

    int sockfd, new_sockfd; 
    int len;
    char buffer[MAXLINE]; 
    struct sockaddr_un server, client;
    int client_size;

    if((sockfd = socket(AF_LOCAL, SOCK_STREAM, 0)) < 0){
        perror(NULL);
        close(sockfd);
        close(new_sockfd);
        exit(1);
    }

    server.sun_family = AF_LOCAL;
    strcpy(server.sun_path, "/tmp/stream_serv");

    if(bind(sockfd, (struct sockaddr *) &server, sizeof(server)) < 0)
    {
        perror(NULL);
        close(sockfd);
        close(new_sockfd);
        exit(1);
    }

    if (listen(sockfd, 5) < 0) {
		perror(NULL);
        close(sockfd);
        close(new_sockfd);
        exit(1);
	}



    if ((new_sockfd = accept(sockfd,(struct sockaddr *)&client, &client_size)) < 0) 
    {
        perror(NULL);
        close(sockfd);
        close(new_sockfd);
        exit(1);
	}

    if((len = recv(new_sockfd, (char *)buffer, MAXLINE, 0)) < 0)
    {
        perror(NULL);
        close(sockfd);
        close(new_sockfd);
        exit(1);
    }

    buffer[len] = '\0'; 
    printf("Client: %s\n", buffer);
    buffer[7] = '2';

    if((len = send(new_sockfd, (char *)buffer, MAXLINE, 0)) < 0)
    {
        perror(NULL);
        close(sockfd);
        close(new_sockfd);
        exit(1);
    }
    close(sockfd);
    close(new_sockfd);

    return 0;
}