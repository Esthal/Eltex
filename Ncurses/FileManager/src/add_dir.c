#include "../FileManager.h"

void add_dir(ManagerDir **List, char *name, long int size)
{
    ManagerDir *temp = malloc(sizeof(struct ManagerDir));;
    int sizeName = strnlen(name, 255) + 1;
    temp->name = malloc(sizeName);
    strcpy(temp->name , name);
    temp->name[sizeName-1] = '\0';
    temp->size = size;
    temp->next = NULL;
    temp->prev = NULL;

    if ((*List) == NULL)
    {
        (*List) = temp;
    }
    else
    {
        ManagerDir *cur = (*List);

        while (cur->next != NULL)
        {
            cur = cur->next;
        }
        cur->next = temp;
        temp->prev = cur;
    }
}