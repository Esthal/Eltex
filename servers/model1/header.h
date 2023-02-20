#define HEADER_H
#ifdef HEADER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <pthread.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <malloc.h>

#define PORT 8000
#define SIZE 256
#define ERROR -1


void set_sockaddr_in(struct sockaddr_in *sock);
void set_socket(int *fd);

#endif