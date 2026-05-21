#include <stdio.h>

int main() {

    int n, i, j;
    int bt[10], pr[10], p[10];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {

        p[i] = i + 1;

        printf("Enter Burst Time and Priority of P%d: ", p[i]);
        scanf("%d %d", &bt[i], &pr[i]);
    }

    // Sorting by priority
    for(i = 0; i < n - 1; i++) {
        for(j = i + 1; j < n; j++) {

            if(pr[i] > pr[j]) {

                int temp;

                temp = pr[i];
                pr[i] = pr[j];
                pr[j] = temp;

                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    printf("\nProcess\tPriority\n");

    for(i = 0; i < n; i++) {
        printf("P%d\t%d\n", p[i], pr[i]);
    }

    return 0;
}
