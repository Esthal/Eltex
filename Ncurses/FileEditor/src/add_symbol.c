#include "../FileEditor.h"

void add_symbol(LINE *current_line, char symbol, int position, int max_size)
{
    if (position < current_line->size)
    {
        current_line->line[position] = symbol;
    }
    else
    {
        if (position < max_size)
        {
            current_line->line = realloc(current_line->line, (position+2) * sizeof(char));
            current_line->line[position] = symbol;
            current_line->line[position+1] = '\0';
            current_line->size = position+1;
        }
    }
}