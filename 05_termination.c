// Practical 5: Fetch and display child termination status
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    int status;

    if (pid > 0) {
        // Parent waits for child
        waitpid(pid, &status, 0);

        if (WIFEXITED(status))
            printf("Child terminated NORMALLY with exit code: %d\n", WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
            printf("Child terminated ABNORMALLY by signal: %d\n", WTERMSIG(status));
    } else if (pid == 0) {
        // Child exits normally
        printf("Child process running...\n");
        // To test abnormal: raise(SIGSEGV);
        return 0;
    } else {
        printf("Fork failed\n");
    }

    return 0;
}

/*
Compile: gcc 05_termination.c -o termination
Run:     ./termination
*/
