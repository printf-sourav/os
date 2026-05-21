// Practical 13: Page Replacement - FIFO, LRU, Optimal
#include <stdio.h>
#include <string.h>

#define MAX 50

int frames[MAX], n, pages[MAX], pg;

int isPresent(int f[], int size, int page) {
    for (int i = 0; i < size; i++)
        if (f[i] == page) return 1;
    return 0;
}

// -------- FIFO --------
void fifo() {
    int frame[MAX], fcount = 0, faults = 0, idx = 0;
    memset(frame, -1, sizeof(frame));

    printf("\n===== FIFO =====\n");
    for (int i = 0; i < pg; i++) {
        printf("Page %d | Frames: ", pages[i]);
        if (!isPresent(frame, n, pages[i])) {
            frame[idx] = pages[i];
            idx = (idx + 1) % n;
            if (fcount < n) fcount++;
            faults++;
            for (int j = 0; j < fcount; j++) printf("%d ", frame[j]);
            printf(" <-- Page Fault\n");
        } else {
            for (int j = 0; j < fcount; j++) printf("%d ", frame[j]);
            printf("\n");
        }
    }
    printf("Total Page Faults (FIFO): %d\n", faults);
}

// -------- LRU --------
void lru() {
    int frame[MAX], last[MAX], fcount = 0, faults = 0;
    memset(frame, -1, sizeof(frame));

    printf("\n===== LRU =====\n");
    for (int i = 0; i < pg; i++) {
        printf("Page %d | Frames: ", pages[i]);
        if (!isPresent(frame, n, pages[i])) {
            faults++;
            if (fcount < n) {
                frame[fcount++] = pages[i];
            } else {
                // Find LRU page (used farthest in past)
                int lruIdx = 0, lruTime = i;
                for (int j = 0; j < n; j++) {
                    int k;
                    for (k = i - 1; k >= 0; k--)
                        if (pages[k] == frame[j]) break;
                    if (k < lruTime) { lruTime = k; lruIdx = j; }
                }
                frame[lruIdx] = pages[i];
            }
            for (int j = 0; j < fcount; j++) printf("%d ", frame[j]);
            printf(" <-- Page Fault\n");
        } else {
            for (int j = 0; j < fcount; j++) printf("%d ", frame[j]);
            printf("\n");
        }
    }
    printf("Total Page Faults (LRU): %d\n", faults);
}

// -------- Optimal --------
void optimal() {
    int frame[MAX], fcount = 0, faults = 0;
    memset(frame, -1, sizeof(frame));

    printf("\n===== Optimal =====\n");
    for (int i = 0; i < pg; i++) {
        printf("Page %d | Frames: ", pages[i]);
        if (!isPresent(frame, n, pages[i])) {
            faults++;
            if (fcount < n) {
                frame[fcount++] = pages[i];
            } else {
                // Find page used farthest in future
                int replaceIdx = 0, farthest = i;
                for (int j = 0; j < n; j++) {
                    int k;
                    for (k = i + 1; k < pg; k++)
                        if (pages[k] == frame[j]) break;
                    if (k > farthest) { farthest = k; replaceIdx = j; }
                }
                frame[replaceIdx] = pages[i];
            }
            for (int j = 0; j < fcount; j++) printf("%d ", frame[j]);
            printf(" <-- Page Fault\n");
        } else {
            for (int j = 0; j < fcount; j++) printf("%d ", frame[j]);
            printf("\n");
        }
    }
    printf("Total Page Faults (Optimal): %d\n", faults);
}

int main() {
    printf("Enter number of frames: "); scanf("%d", &n);
    printf("Enter number of pages : "); scanf("%d", &pg);
    printf("Enter page reference string: ");
    for (int i = 0; i < pg; i++) scanf("%d", &pages[i]);

    int choice;
    printf("\n1. FIFO\n2. LRU\n3. Optimal\n4. All\nChoice: ");
    scanf("%d", &choice);

    if (choice == 1 || choice == 4) fifo();
    if (choice == 2 || choice == 4) lru();
    if (choice == 3 || choice == 4) optimal();

    return 0;
}

/*
Compile: gcc 13_page_replacement.c -o pagerep
Run:     ./pagerep

Sample Input:
  Frames : 3
  Pages  : 12
  String : 7 0 1 2 0 3 0 4 2 3 0 3
*/
