#include "../FileManager.h"

void read_dir(char *cwd, ManagerDir **List)
{
    struct dirent **namelist;
    struct stat info;

    int n;
    int i = 1;

    int count_files = scandir(cwd, &namelist, 0, alphasort);
    if (count_files < 0)
        perror("scandir");
    else {
        while(i < count_files) {
            stat(namelist[i]->d_name, &info);
            if (namelist[i]->d_type == 8)
            {
                add_dir(List, namelist[i]->d_name, info.st_size);
            }
            else
            {
                add_dir(List, namelist[i]->d_name, -1);
            }
            free(namelist[i]);
            i++;
        }
        free(namelist);
    }
}