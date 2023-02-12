#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



#define PORT 8000
#define MAXLINE 20 


int main()
{
    int sockfd; 
    int clilen, len;
    char buffer[MAXLINE]; 
    struct sockaddr_in server, client; 

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        perror(NULL);
        exit(1);
    }
    
    bzero(&server, sizeof(server));
    server.sin_family    = AF_INET; 
    server.sin_addr.s_addr = INADDR_ANY; 
    server.sin_port = htons(PORT); 

    if(bind(sockfd, (struct sockaddr *) &server, sizeof(server)) < 0)
    {
        perror(NULL);
        close(sockfd);
        exit(1);
    }  

    clilen = sizeof(client);
    if((len = recvfrom(sockfd, buffer, MAXLINE, 0, (struct sockaddr *) &client, &clilen)) < 0)
    {
        perror(NULL);
        close(sockfd);
        exit(1);
    }
    buffer[len] = '\0'; 
    printf("Client: %s\n", buffer);

    buffer[7] = '2';

    if(sendto(sockfd, (const char *)buffer, len, 0, (struct sockaddr *) &client, clilen) < 0)
    {
        perror(NULL);
        close(sockfd);
        exit(1);
    }

    close(sockfd);
}