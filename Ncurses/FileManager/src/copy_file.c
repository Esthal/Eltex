#include "../FileManager.h"

void copy_file(char *cwd, char *name)
{
    char old_path[PATH_MAX];
    char new_path[PATH_MAX];

    strcpy(old_path, ".");
    strcat(old_path, cwd);
    strcat(old_path, "/");
    strcat(old_path, name);

    strcpy(new_path, old_path);
    strcat(new_path, "-copy");

    int pid = fork();
    int status;

    if(pid == 0)
    {
        if (execlp("cp", "cp", old_path, new_path, NULL) == -1)
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