#include "../FileManager.h"

void move_it(char *old_path, char *new_path)
{
    int pid = fork();
    int status;
    if(pid == 0)
    {
        
        if (execlp("mv", "mv", old_path, new_path, NULL) == -1)
        {            
            exit(EXIT_FAILURE);
        }
    }
     
    do 
    {
        waitpid(pid, &status, WUNTRACED);
    } 
    while (!WIFEXITED(status) && !WIFSIGNALED(status));
}