#include "bash.h"

int main(void)
{
    char *cmd_row;
    char **split_row;
    do
    {
        printf("> ");
        cmd_row = read_line();

        if(strcmp(cmd_row, "exit\n") == 0)
        {
            break;
        }

        if(cmd_row[0] == ' ' || cmd_row[0] == '\n' || cmd_row[0] == '\0')
        {
            printf("Enter a command\n");
            continue;
        }

        split_row = split_line(cmd_row);
        execute(split_row);
        
        free(cmd_row);
        free(split_row);

    }
    while (1);

    return 0;
}
