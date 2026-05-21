// Practical 6: Communication between two unrelated processes using Named Pipe (FIFO)
// Run writer first in one terminal, then reader in another terminal

// ===== WRITER (writer.c) =====
// #include <stdio.h>
// #include <fcntl.h>
// #include <sys/stat.h>
// #include <string.h>
// int main() {
//     mkfifo("/tmp/myfifo", 0666);
//     int fd = open("/tmp/myfifo", O_WRONLY);
//     char msg[] = "Hello from Writer!";
//     write(fd, msg, strlen(msg) + 1);
//     close(fd);
//     return 0;
// }

// ===== COMBINED VERSION (both in one file using fork) =====
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main() {
    char *fifo = "/tmp/myfifo";
    mkfifo(fifo, 0666);

    pid_t pid = fork();

    if (pid > 0) {
        // Parent = Writer
        int fd = open(fifo, O_WRONLY);
        char msg[] = "Hello from Writer process!";
        write(fd, msg, strlen(msg) + 1);
        close(fd);
        wait(NULL);
        unlink(fifo);
    } else if (pid == 0) {
        // Child = Reader
        int fd = open(fifo, O_RDONLY);
        char buf[100];
        read(fd, buf, sizeof(buf));
        printf("Reader received: %s\n", buf);
        close(fd);
    }

    return 0;
}

/*
Compile: gcc 06_fifo.c -o fifo
Run:     ./fifo
*/
