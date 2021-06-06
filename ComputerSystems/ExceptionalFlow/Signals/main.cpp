#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>

void unix_error(const char *msg) /* Unix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

void kill_sample() {
    pid_t pid;

    /* Child sleeps until SIGKILL signal received, then dies */
    if ((pid = fork()) == 0) {
        pause(); /* Wait for a signal to arrive */
        printf("control should never reach here!\n");
        exit(0);
    }

    /* Parent sends a SIGKILL signal to a child */
    kill(pid, SIGKILL);
    exit(0);
}

void sigint_handler(int sig) /* SIGINT handler */
{
    printf("Caught SIGINT!\n");
    exit(0);
}

int signal_handler_sample() {
    /* Install the SIGINT handler */
    if (signal(SIGINT, sigint_handler) == SIG_ERR)
        unix_error("signal error");
    pause(); /* Wait for the receipt of a signal */
    return 0;
}

int main() {
}