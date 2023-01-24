#include "../FileEditor.h"

void key_down(LINE **head, LINE **current_line, WINDOW *text_field, int max_size_line, int *lines_count, int lines_max, int *cur_line)
{
    int x,y;
    getyx(text_field, y, x);

    if ((*cur_line) <= lines_max-2)
    {
        (*cur_line)++;
    }
    else
    {
        clear_text(text_field, max_size_line, lines_max);
        (*head) = (*head)->next;
        print_text((*head), text_field, lines_max);
        y--;
    }
    
    if((*current_line)->next == NULL)
    {
        if ((*lines_count) < lines_max-2)
        {
            (*lines_count)++;
        } 
        LINE *temp = malloc(sizeof(LINE));
        temp->line = (char *)malloc(sizeof(char));     
        temp->line[0] = '\0';
        temp->size = 0;       
        temp->prev = (*current_line);
        temp->next = NULL;

        (*current_line)->next = temp;
        (*current_line) = (*current_line)->next;
        wmove(text_field, y+1, 0);
    }
    else
    {
        (*current_line) = (*current_line)->next;
        if(x < (*current_line)->size)
        {
            wmove(text_field, y+1, x);
        }
        else
        {
            wmove(text_field, y+1, (*current_line)->size);
        }
    }
    
    
    
    
}