#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <time.h>

int running = 1;
int interrupted = 0;
int last_mode = -1;
int mode_changes = 0;

void check_for_mode_change(int mode) {
    if (mode > 0 && mode < 4 && mode != last_mode) {
        mode_changes++;
        last_mode = mode;
    }
}

void signal_handler(int sig, siginfo_t *info, void *context) {
    kill(info->si_pid, SIGUSR1);
    
    int mode = info->si_value.sival_int;

    check_for_mode_change(mode);

    switch (mode) {
        case 1:
            interrupted = 1;
            for (int i = 1; i < 101; ++i) printf("%d ", i);
            printf("\n");
            break;
        case 2:
            interrupted = 1;
            printf("Mode changes occured: %d\n", mode_changes);
            break;
        case 3:
            interrupted = 1;
            running = 0;
            printf("Catcher closed!\n");
            return;
        default:
            interrupted = 1;
            printf("Mode %d not defined.\n", mode);
            break;
    }
    printf("______________________________________________________\n");
}

int main(int argc, char** argv) {  
    printf("My pid: %d\n", getpid());
    printf("______________________________________________________\n");

    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = signal_handler;
    sigaction(SIGUSR1, &sa, NULL);

    while(running) {
        if(!interrupted) sleep(1);
    }

    return 0;
}