#include <pwd.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "sanitize.h"


int ask_confirmation()
{
    char input[100];

    printf("Welcome to PleaseStopSpinningMe, if you want to get rid of the confloose, please type \"yes\" : ");
    scanf("%99s", input);

    if (strcmp(input, "yes") == 0) {
        return 1;
    }

    return 0;
}

int del_payload()
{
    char* string;
    if(0 > asprintf(&string, "rm -rf %s/afs/.local", (getpwuid(geteuid())->pw_dir))) return EXIT_FAILURE;
    printf("Executed %s\nThe payload was stored in this file in order to autostart\n", string);
    system(string);
    free(string);
    string = NULL;
    return 0;
}

int kill_process()
{
    char *string;
    printf("Reading the lock file in order to kill the process\n");
    FILE *f = fopen("/tmp/spin.pid", "r");

    if (!f)
    {
        printf("Unable to read .lock file\n");
        return EXIT_FAILURE;
    }

    char *buffer;
    size_t t = 0;
    getline(&buffer, &t, f);
    pid_t pid = atoi(buffer);
    free(buffer);
    fclose(f);

    printf("Killing confloose\n");
    if(0 > asprintf(&string, "kill %d", pid)) return EXIT_FAILURE;
    system(string);
    free(string);
    return 0;
}

int remove_lock()
{
    if (remove("/tmp/spin.pid") == 0)
    {
        printf("Deleted lock file\n");
        return 0;
    }

    printf("Lock file doesn't exist, continuing removal\n");
    return 1;
    
}

int sanitize()
{
    system("xrandr -o normal");
    del_payload();
    kill_process();
    remove_lock();
    printf("Confloose cleaned, you can now delete the starting line in bashrc.\n");
    system("xrandr -o normal");
    return 0;
}

int main(void)
{
    if (!ask_confirmation())
        return EXIT_FAILURE;

    sanitize();
    system("xrandr -o normal"); //If the payload triggered during cleanup

    return 0;
}