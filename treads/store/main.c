#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>

#define STORES 5
#define CLIENT 3



int store[STORES];
pthread_mutex_t mtx[STORES] = PTHREAD_MUTEX_INITIALIZER;

void *client_thread(void *arg)
{
    pthread_t id = pthread_self();
    int store_number;
    int s;
    while (*((int *)arg) > 0)
    {
        store_number = rand() % 5;
        s = pthread_mutex_lock(&mtx[store_number]);
        printf("client (%ld) go into store #%d\n", id, store_number);
        if(s == 0)
        {
            printf("client (%ld) need %d\n", id, *((int *)arg));
            if (store[store_number] >= *((int *)arg))
            {
                printf("client (%ld) buy %d goods\n", id, *((int *)arg));
                store[store_number] -= *((int *)arg);
                *((int *)arg) = 0;
            }
            else
            {
                printf("client (%ld) buy %d goods\n", id, store[store_number]);
                *((int *)arg) -= store[store_number];
                store[store_number] = 0;
            }
            printf("client (%ld) still need %d\n", id, *((int *)arg));
            s = pthread_mutex_unlock(&mtx[store_number]);
            if (s != 0)
            {
                perror("mutex: unlock\n");
            }
        }
        
        sleep(2);
    }
    printf("client(%ld) finished buying\n", id);
    return NULL;
}
void *loader_thread(void *arg)
{
    int store_number;
    int s;
    
    printf("loader: %d\n", *((int *)arg));
    
    while (1)
    {
        store_number = rand() % 5;
        s = pthread_mutex_lock(&mtx[store_number]);
        if(s == 0)
        {            
            store[store_number] += *((int *)arg);
            s = pthread_mutex_unlock(&mtx[store_number]);
            if (s != 0)
            {
                perror("mutex loader: unlock\n");
            }
            printf("put 500 goods into store #%d:\n",store_number);
        }
        

        sleep(1);
    }
    return NULL;
}
int main(void)
{
    srand(time(NULL));
    for (int i = 0; i < STORES; i++)
    {
        store[i] = 950+(rand()%100);
    }


    int need_goods[3];
    int new_goods = 500;
    for (int i = 0; i < STORES; i++)
    {
        need_goods[i] = 5000+(rand()%500);
        printf("store %d: %d\n",i, store[i]);
    }

    pthread_t index[CLIENT+1];
    int s;
    int *res;
    for (int i = 0; i < CLIENT; i++)
    {
        s = pthread_create(&index[i], NULL, client_thread, &need_goods[i]);
        if (s != 0)
        {
            perror("error: create\n");
        }
    }
    s = pthread_create(&index[CLIENT], NULL, loader_thread, &new_goods);
    if (s != 0)
    {
        perror("error: create\n");
    }
    for (int i = 0; i < CLIENT; i++)
    {
        s = pthread_join(index[i], (void **) &res);
        if (s != 0)
        {
            perror("error: join\n");
        }
    }
    pthread_cancel(index[CLIENT+1]);

    exit(EXIT_SUCCESS);
}