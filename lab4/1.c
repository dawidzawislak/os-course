#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <string.h>

void my_handler(int signum) {
    printf("Recieved SIGUSR1\n");
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Pass argument (none/ignore/handler/mask)!\n");
        return -1;
    }

    if (strcmp(argv[1], "none") == 0) {
        signal(SIGUSR1, SIG_DFL);
    }
    else if (strcmp(argv[1], "ignore") == 0) {
        signal(SIGUSR1, SIG_IGN);
    }
    else if (strcmp(argv[1], "handler") == 0) {
        signal(SIGUSR1, my_handler);
    }
    else if (strcmp(argv[1], "mask") == 0) {
        sigset_t newmask;
        sigset_t oldmask;
        sigemptyset(&newmask);
        sigaddset(&newmask, SIGUSR1);

        if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) 
            perror("Couldn't block signal!\n"); 
    }
    else {
        printf("Option not defined!\n");
        return -2;
    }

    raise(SIGUSR1);

    sigset_t pending;
    sigpending(&pending);

    if (sigismember(&pending, SIGUSR1)) {
        printf("Signal is pending\n");
    }
    else {
        printf("Signal is not pending\n");
    }

    return 0;
}