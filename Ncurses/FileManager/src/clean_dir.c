#include "../FileManager.h"

void clean_dir(ManagerDir **List)
{
    while ((*List)->prev != NULL)
    {
        (*List) = (*List)->prev;
    }

    ManagerDir *temp = (*List);
    
    while ((*List) != NULL)
    {
        (*List) = (*List)->next;

        free(temp->name);
        free(temp);        
        temp->next = NULL;
        temp->prev = NULL;
        temp = (*List);
    }
}