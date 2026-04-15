#include "init.h"
#include <signal.h>

void handle_signal(int sig)
{
    running = 0;
}

int create_lock(const char *path)
{
    pid_fd = open(path, O_RDWR | O_CREAT, 0640);
    if (pid_fd < 0)
        return -1;

    struct flock fl;
    memset(&fl, 0, sizeof(fl));

    fl.l_type = F_WRLCK;
    fl.l_whence = SEEK_SET;

    if (fcntl(pid_fd, F_SETLK, &fl) < 0)
        return -1;

    return 0;
}

void write_pid()
{
    char buf[32];

    ftruncate(pid_fd, 0);
    snprintf(buf, sizeof(buf), "%ld\n", (long)getpid());
    write(pid_fd, buf, strlen(buf));
}

void daemonize()
{
    pid_t pid;

    pid = fork();
    if (pid < 0)
        exit(EXIT_FAILURE);

    if (pid > 0)
        exit(EXIT_SUCCESS);

    if (setsid() < 0)
        exit(EXIT_FAILURE);

    pid = fork();
    if (pid < 0)
        exit(EXIT_FAILURE);

    if (pid > 0)
        exit(EXIT_SUCCESS);

    umask(0);

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    open("/dev/null", O_RDONLY);
    open("/dev/null", O_RDWR);
    open("/dev/null", O_RDWR);
}

void setup_signals()
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));

    sa.sa_handler = handle_signal;

    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGKILL, &sa, NULL);
    sigaction(SIGINT, &sa, NULL);
}

