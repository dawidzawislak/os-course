#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int running = 1;

void signal_response_handler(int sigid){
    printf("Catcher recieved signal!\n");
    running = 0;
}

int main(int argc, char** argv) {  
    if (argc != 3) {
        printf("Pass 2 arguments!\n");
        return -1;
    }
    pid_t catcher_id;
    int mode;
    sscanf(argv[1], "%d", &catcher_id);
    sscanf(argv[2], "%d", &mode);

    union sigval sigspec;
    signal(SIGUSR1, signal_response_handler);

    sigspec.sival_int = mode;
    printf("Sending SIGUSR1 to catche with mode %d\n", mode);
    sigqueue(catcher_id, SIGUSR1, sigspec);
    printf("Waiting for catcher to recieve signal..\n");
    while(running);
    
    return 0;
}