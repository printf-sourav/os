// Practical 11: Banker's Algorithm (Deadlock Avoidance)
#include <stdio.h>

#define MAX_P 10
#define MAX_R 10

int main() {
    int n, m;
    int alloc[MAX_P][MAX_R], max[MAX_P][MAX_R], need[MAX_P][MAX_R];
    int avail[MAX_R], finish[MAX_P] = {0};
    int safeSeq[MAX_P], work[MAX_R];

    printf("Enter number of processes and resources: ");
    scanf("%d %d", &n, &m);

    printf("Enter Allocation matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Maximum matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
            need[i][j] = max[i][j] - alloc[i][j];
        }

    printf("Enter Available resources: ");
    for (int j = 0; j < m; j++) { scanf("%d", &avail[j]); work[j] = avail[j]; }

    // Safety Algorithm
    int count = 0;
    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int ok = 1;
                for (int j = 0; j < m; j++)
                    if (need[i][j] > work[j]) { ok = 0; break; }
                if (ok) {
                    for (int j = 0; j < m; j++) work[j] += alloc[i][j];
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) { printf("System is in UNSAFE state (Deadlock possible)\n"); return 0; }
    }

    printf("System is in SAFE state\nSafe Sequence: ");
    for (int i = 0; i < n; i++)
        printf("P%d%s", safeSeq[i], i < n-1 ? " -> " : "\n");

    return 0;
}

/*
Compile: gcc 11_bankers.c -o bankers
Run:     ./bankers

Sample Input:
  Processes: 5, Resources: 3
  Allocation:
    0 1 0
    2 0 0
    3 0 2
    2 1 1
    0 0 2
  Maximum:
    7 5 3
    3 2 2
    9 0 2
    2 2 2
    4 3 3
  Available: 3 3 2
*/
