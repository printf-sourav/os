// Practical 12: Check if last 100 bytes are locked; if not, lock, read 50 bytes, unlock
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc < 2) { printf("Usage: ./a.out filename\n"); return 1; }

    int fd = open(argv[1], O_RDWR);
    if (fd < 0) { perror("open"); return 1; }

    struct stat st;
    fstat(fd, &st);
    off_t start = st.st_size > 100 ? st.st_size - 100 : 0;

    struct flock fl;
    fl.l_type   = F_RDLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start  = start;
    fl.l_len    = 100;

    // Check if region is locked
    if (fcntl(fd, F_GETLK, &fl) < 0) { perror("fcntl"); return 1; }

    if (fl.l_type != F_UNLCK) {
        printf("Region is LOCKED by PID: %d\n", fl.l_pid);
    } else {
        printf("Region is NOT locked. Locking now...\n");

        // Apply exclusive lock
        fl.l_type = F_WRLCK;
        fcntl(fd, F_SETLK, &fl);

        // Read last 50 bytes
        char buf[51] = {0};
        off_t readStart = st.st_size > 50 ? st.st_size - 50 : 0;
        lseek(fd, readStart, SEEK_SET);
        int n = read(fd, buf, 50);
        printf("Last 50 bytes read (%d bytes): %s\n", n, buf);

        // Unlock
        fl.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &fl);
        printf("Region unlocked.\n");
    }

    close(fd);
    return 0;
}

/*
Compile: gcc 12_file_lock.c -o filelock
Create test file: echo "This is a test file with enough content to test last 100 bytes locking mechanism in this program" > test.txt
Run:     ./filelock test.txt
*/
