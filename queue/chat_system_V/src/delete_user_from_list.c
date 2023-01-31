#include "../client.h"

void delete_user_from_list(chat **list,char *name)
{
    chat *temp = (*list);

    while (temp != NULL)
    {
        if (strcmp(temp->mes, name) == 0)
        {
            if(temp->prev == NULL && temp->next == NULL)
            {
                free(temp);
                (*list)->next = NULL;
                (*list)->prev = NULL;
                (*list) = NULL;
            }
            else if (temp->prev == NULL)
            {
                (*list) = (*list)->next;
                (*list)->prev = NULL;
                free(temp);
            }
            else if (temp->next == NULL)
            {
                temp = temp->prev;
                temp->next = NULL;
                free(temp->next);
            }
            else
            {
                temp->next->prev = temp->prev;
                temp->prev->next = temp->next;
                temp->next == NULL;
                temp->prev == NULL;
                free(temp);
            }
            break;
            
        }
        temp = temp->next;
    }

}