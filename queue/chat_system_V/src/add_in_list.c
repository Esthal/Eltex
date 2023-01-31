#include "../client.h"

void add_in_list(chat **list,char *mes)
{
    chat *temp = malloc(sizeof(struct mes_chat));
    strcpy(temp->mes , mes);
    temp->next = NULL;
    temp->prev = NULL;

    if ((*list) == NULL)
    {
        (*list) = temp;
    }
    else
    {
        chat *cur = (*list);

        while (cur->next != NULL)
        {
            cur = cur->next;
        }
        cur->next = temp;
        temp->prev = cur;
    }
}