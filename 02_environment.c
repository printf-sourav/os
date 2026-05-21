// Practical 2: Print environment list
#include <stdio.h>

int main(int argc, char *argv[], char *envp[]) {
    int i = 0;
    printf("Environment Variables:\n");
    while (envp[i] != NULL) {
        printf("%s\n", envp[i]);
        i++;
    }
    return 0;
}

/*
Compile: gcc 02_environment.c -o env
Run:     ./env
*/
