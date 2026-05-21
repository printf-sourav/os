// Practical 3: Check system limits
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

int main() {
    printf("a. Clock ticks per second : %ld\n", sysconf(_SC_CLK_TCK));
    printf("b. Max child processes    : %ld\n", sysconf(_SC_CHILD_MAX));
    printf("c. Max path length        : %d\n",  PATH_MAX);
    printf("d. Max filename length    : %d\n",  NAME_MAX);
    printf("e. Max open files         : %ld\n", sysconf(_SC_OPEN_MAX));
    return 0;
}

/*
Compile: gcc 03_limits.c -o limits
Run:     ./limits
*/
