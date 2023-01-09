#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

#define SIZE 5

int a;


void *thread_func(void *arg)
{
    int tmp;
    for (int i = 0; i < 100000; i++)
    {
        tmp = a;
        tmp++;
        a = tmp;
    }
    
    return NULL;
}

int main()
{
    a = 0;
    pthread_t index[SIZE];
    int *res;

    int s;
    for (int i = 0; i < SIZE; i++)
    {
        s = pthread_create(&index[i],NULL,thread_func,NULL);
        if (s != 0)
        {
            perror("error: create\n");
        }
    }
    
    for (int i = 0; i < SIZE; i++)
    {
        s = pthread_join(index[i], (void **)&res);
        if (s != 0)
        {
            perror("error: join\n");
        }
    }

    printf("result: %d\n", a);
    exit(EXIT_SUCCESS);
}