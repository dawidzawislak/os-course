#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
    int count = atoi(argv[1]);
    
    printf("PID glownego programu: %d\n", (int)getpid());

    for (int i = 0; i < count; ++i) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Error while creating child process");
        }
        if (pid == 0) {
            printf("(%d) Process ID: %d | Parent ID: %d \n", i+1, (int)getpid(), (int)getppid());
            return 0;
        } 
        else {
            wait(NULL);
        }
    }
    
    printf("argv[1]: %s\n", argv[1]);

    return 0;
}