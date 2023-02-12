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
    int sockfd, len; 
    char buffer[MAXLINE]; 
    struct sockaddr_in server; 


    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror(NULL);
        exit(1);
    }
    
        
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET; 
    server.sin_port = htons(PORT);


    if(connect(sockfd, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        perror("connect()");
        close(sockfd);
        exit(1);
    }


    strcpy(buffer, "Hello, 1!");

    if(sendto(sockfd, (const char *)buffer, strlen(buffer), 0, (struct sockaddr *) &server, sizeof(server)) < 0)
    {
        perror(NULL);
        close(sockfd);
        exit(1);
    }
    
    if((len = recvfrom(sockfd, (char *)buffer, MAXLINE, 0, (struct sockaddr *) NULL, NULL)) < 0)
    {
        perror(NULL);
        close(sockfd);
        exit(1);
    }

    buffer[len] = '\0'; 
    printf("Server: %s\n", buffer); 
    
    close(sockfd);

    return 0;
}