// Practical 10: Query and display file attributes
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc < 2) { printf("Usage: ./a.out filename\n"); return 1; }

    struct stat s;
    if (stat(argv[1], &s) < 0) { perror("stat"); return 1; }

    printf("File         : %s\n",  argv[1]);
    printf("Inode        : %lu\n", s.st_ino);
    printf("Size (bytes) : %ld\n", s.st_size);
    printf("Hard Links   : %lu\n", s.st_nlink);
    printf("UID          : %d\n",  s.st_uid);
    printf("GID          : %d\n",  s.st_gid);
    printf("Permissions  : %o\n",  s.st_mode & 0777);
    printf("Last Access  : %s",    ctime(&s.st_atime));
    printf("Last Modified: %s",    ctime(&s.st_mtime));
    printf("Last Changed : %s",    ctime(&s.st_ctime));

    if (S_ISREG(s.st_mode))       printf("Type: Regular file\n");
    else if (S_ISDIR(s.st_mode))  printf("Type: Directory\n");
    else if (S_ISLNK(s.st_mode))  printf("Type: Symbolic link\n");

    return 0;
}

/*
Compile: gcc 10_file_attr.c -o fileattr
Run:     ./fileattr myfile.txt
*/
