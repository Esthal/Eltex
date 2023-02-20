#include "header.h"



int main(void)
{

    struct sockaddr_in server;
    int fd_passive;


    set_sockaddr_in(&server);
    set_socket(&fd_passive);


    int len;
    char buffer[SIZE]; 

    strcpy(buffer, "Hello, 1!");

    if (connect(fd_passive, (struct sockaddr*)&server, sizeof(server)) < 0) {
		printf("could not connect to server\n");
		return 1;
	}

    if((len = send(fd_passive, (char *)buffer, SIZE, 0)) < 0)
    {
        perror(NULL);
        close(fd_passive);
        exit(1);
    }

    if((len = recv(fd_passive, (char *)buffer, SIZE, 0)) < 0)
    {
        perror(NULL);
        close(fd_passive);
        exit(1);
    }

    buffer[len] = '\0'; 
    printf("Server: %s\n", buffer);

    close(fd_passive);
    return 0;
}
void set_sockaddr_in(struct sockaddr_in *sock)
{
    sock->sin_family = AF_INET;
    sock->sin_port = htons(PORT);
    sock->sin_addr.s_addr = htonl(INADDR_LOOPBACK);
}

void set_socket(int *fd)
{
    *fd = socket(AF_INET, SOCK_STREAM, 0);
    if(*fd == ERROR)
    {
        perror("socket()"); 
        exit(EXIT_FAILURE);
    }
}