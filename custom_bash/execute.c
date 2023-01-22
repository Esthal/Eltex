#include "bash.h"

void execute(char **split_row)
{
    
    int position = 0;
    int cmd = 0;
    int count_cmd = 0;
    int command_num = 0;

    char **cmds = (char**)malloc(sizeof(char*) * 64);
    char ***cmds_argv = (char***)malloc(sizeof(char**) * 64);
    

    while (split_row[position] != NULL)
    {
        if (strcmp(split_row[position], "|") == 0)
        {
            position++;
            count_cmd++;
            cmd=0;
            command_num = 0;
            continue;
        }
        if (cmd == 0)
        {
            cmds[count_cmd] = malloc(sizeof(char) * 64);
            cmds_argv[count_cmd] = (char**)malloc(sizeof(char*) * 64);
            cmds_argv[count_cmd][command_num] = (char*)malloc(sizeof(char) * 64);

            strcat(cmds[count_cmd], split_row[position]);
            strcat(cmds_argv[count_cmd][command_num], split_row[position]);
            
            cmd++;
            command_num++;
        }
        else
        {
            cmds_argv[count_cmd][command_num] = (char*)malloc(sizeof(char) * 64);

            strcat(cmds_argv[count_cmd][command_num], split_row[position]);

            command_num++;
        }
 
        position++;
    }
    cmds_argv[count_cmd][command_num] = (char*)malloc(sizeof(char) * 64);
    cmds_argv[count_cmd][command_num] = NULL;



    int fd[count_cmd+1][2];
    pid_t pid;
    int status = 0;

    for(int i = 0; i <= count_cmd; i++) 
    {
        if (pipe(fd[i]) == -1) 
        {
            fprintf(stderr, "pipe error\n");
        }
    }

    for (int i = 0; i <= count_cmd; i++)
    {
        pid = fork();
        if (pid == 0) 
        {
            dup2(fd[i][0], 0);
            if(i != count_cmd)
            {
                dup2(fd[i+1][1], 1);
            }
            close(fd[i][0]);
            close(fd[i][1]);


            if (execvp(cmds[i], cmds_argv[i]) == -1)
            {
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        }
        close(fd[i][0]);
        close(fd[i][1]);
        do 
        {
            waitpid(pid, &status, WUNTRACED);
        } 
        while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}