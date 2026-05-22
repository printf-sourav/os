#include <stdio.h>

int main() {

    int n, m, i, j, count = 0;

    printf("Enter number of processes and resources: ");
    scanf("%d %d", &n, &m);

    int alloc[10][10], max[10][10], need[10][10];
    int avail[10], finish[10] = {0};

    printf("Enter Allocation Matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Max Matrix:\n");
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);

            need[i][j] = max[i][j] - alloc[i][j];
        }

    printf("Enter Available Resources:\n");
    for(i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    printf("Safe Sequence: ");

    for(i = 0; i < n; i++) {

        for(j = 0; j < n; j++) {

            if(finish[j] == 0) {

                int safe = 1;

                for(int k = 0; k < m; k++) {

                    if(need[j][k] > avail[k]) {
                        safe = 0;
                        break;
                    }
                }

                if(safe) {

                    printf("P%d ", j);

                    finish[j] = 1;

                    count++;

                    for(int k = 0; k < m; k++)
                        avail[k] += alloc[j][k];
                }
            }
        }
    }

    if(count == n)
        printf("\nSystem is in SAFE state\n");
    else
        printf("\nSystem is NOT in SAFE state\n");

    return 0;
}