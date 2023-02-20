#include "header.h"

void *threads_func(void *args);


int main(void)
{
    struct sockaddr_in server;
    int fd_passive;


    set_sockaddr_in(&server);
    set_socket(&fd_passive);

    if(bind(fd_passive, (const struct sockaddr *) &server, sizeof(struct sockaddr_in)) == ERROR){
        perror("bind()"); 
        exit(EXIT_FAILURE);
    }

    if(listen(fd_passive, 5) == ERROR)
    {
        perror("listen()"); 
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        struct sockaddr_in client;
        int client_size = sizeof(client);
        int client_fd;
        if ((client_fd = accept(fd_passive,(struct sockaddr *)&client, &client_size)) < 0) 
        {
            perror("client accept err");
			continue;
        }
        pthread_t thread_index;
        int *new_fd = malloc(sizeof(int));
        *new_fd = client_fd;
        pthread_create(&thread_index, NULL, (void*)threads_func, (void*) new_fd);
    }
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
void *threads_func(void *args){
    int fd = *((int *)args);
    char buffer[255];
    int len;

    memset(buffer, '\0', sizeof(buffer));

    len = recv(fd, (char *)buffer, SIZE, 0);

    buffer[len] = '\0'; 
    printf("Client: %s\n", buffer);
    buffer[7] = '2';

    len = send(fd, (char *)buffer, SIZE, 0);

	close(fd);
}

