#include "../FileEditor.h"

int file_exists(char *filename)
{
    FILE *fp = fopen(filename, "r");
    if(fp != NULL) {
        fclose(fp);
        return TRUE;
    }
    return FALSE;
}