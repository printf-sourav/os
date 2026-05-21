// Practical 4: Parent prints "parent", child copies file
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: ./a.out source.txt dest.txt\n");
        return 1;
    }

    pid_t pid = fork();

    if (pid > 0) {
        // Parent process
        printf("Parent\n");
        wait(NULL);
    } else if (pid == 0) {
        // Child process: run cp command
        execlp("cp", "cp", argv[1], argv[2], NULL);
    } else {
        printf("Fork failed\n");
    }

    return 0;
}

/*
Compile: gcc 04_fork_copy.c -o fork_copy
Run:     ./fork_copy source.txt dest.txt
*/
