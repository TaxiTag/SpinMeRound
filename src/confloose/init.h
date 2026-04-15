#ifndef INIT_H
#define INIT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <sys/stat.h>

#define PIDFILE "/tmp/spin.pid"

/*Checks if the confloose is currently runnning*/
int is_process_running(void);

/*Creates a lock file to ensure that the process is runnning only once*/
int create_lock(const char *path);

/*Wait for signals to handle*/
void setup_signals(void);

/*Stops the process if signal is received*/
void handle_signal(int sig);

/*Writes the process id to lock file*/
void write_pid(void);

/*Starts the daemon*/
void daemonize(void);

static int pid_fd = -1;
static volatile sig_atomic_t running = 1;

#endif