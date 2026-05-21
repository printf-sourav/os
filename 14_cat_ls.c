// Practical 14: User-defined cat and ls commands
#include <stdio.h>
#include <string.h>
#include <dirent.h>

// Custom cat: print file contents to stdout
void my_cat(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) { perror(filename); return; }
    char ch;
    while ((ch = fgetc(fp)) != EOF)
        putchar(ch);
    fclose(fp);
}

// Custom ls: list files in a directory
void my_ls(const char *path) {
    DIR *dir = opendir(path);
    if (!dir) { perror(path); return; }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // Skip hidden files (starting with '.')
        if (entry->d_name[0] != '.')
            printf("%s\n", entry->d_name);
    }
    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage:\n");
        printf("  ./a.out cat <filename>\n");
        printf("  ./a.out ls  [directory]\n");
        return 1;
    }

    if (strcmp(argv[1], "cat") == 0) {
        if (argc < 3) { printf("cat: missing filename\n"); return 1; }
        my_cat(argv[2]);
    } else if (strcmp(argv[1], "ls") == 0) {
        my_ls(argc >= 3 ? argv[2] : ".");
    } else {
        printf("Unknown command: %s\n", argv[1]);
    }

    return 0;
}

/*
Compile: gcc 14_cat_ls.c -o mycommands
Run:     ./mycommands cat myfile.txt
         ./mycommands ls .
         ./mycommands ls /home
*/
