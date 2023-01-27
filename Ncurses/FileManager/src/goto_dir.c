#include "../FileManager.h"

void goto_dir(ManagerDir **list, ManagerDir *cur_list, char *cwd)
{   
    if(cur_list != NULL)
    {
        if(strcmp(cur_list->name, "..") == 0)
        {
            for (int i = strlen(cwd); i > 0; i--)
            {
                if (cwd[i] != '/')
                {
                    cwd[i] = '\0';
                    continue;
                }
                cwd[i] = '\0';
                break;
            }
        }
        else
        {
            strcat(cwd, "/");
            strcat(cwd, cur_list->name);
        }        

        clean_dir(list);
        read_dir(cwd, list);
    }
}