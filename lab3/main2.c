#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int global = 0;

int main(int argc, char** argv) {

    pid_t pid = fork();

    int local = 0;

    int errCode = 0;

    if (pid < 0) {
        perror("Error while creating child process");
    }
    if (pid == 0) {
        local++;
        global++;
        printf("\nchild process\n");

        printf("Child ID: %d | Parent ID: %d \n", (int)getpid(), (int)getppid());
        printf("Child's local: %d | Child's global: %d \n", local, global);
        return execl("/bin/ls", "ls", argv[1], NULL);
    } 
    else {
        int status;
        wait(&status);
        errCode = WEXITSTATUS(status);
        printf("\nparent process\n");
        printf("Parent ID: %d | Child ID: %d \n", (int)getpid(), pid);
        printf("Child exit code: %d\n", errCode);
        printf("Parents's local: %d | Parents's global: %d \n", local, global);
    }
    

    return errCode;
}