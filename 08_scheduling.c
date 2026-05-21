// Practical 8: CPU Scheduling - FCFS, SJF, SRTF, Priority
#include <stdio.h>
#include <string.h>

#define MAX 10

typedef struct {
    int pid, at, bt, priority;
    int ct, tat, wt;
    int remaining;
} Process;

void input(Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Process %d - Arrival Time: ", i + 1); scanf("%d", &p[i].at);
        printf("Process %d - Burst Time  : ", i + 1); scanf("%d", &p[i].bt);
        printf("Process %d - Priority    : ", i + 1); scanf("%d", &p[i].priority);
        p[i].remaining = p[i].bt;
    }
}

void printResults(Process p[], int n, char *algo) {
    float totalTAT = 0, totalWT = 0;
    printf("\n===== %s =====\n", algo);
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        totalTAT += p[i].tat;
        totalWT  += p[i].wt;
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
            p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("Avg TAT: %.2f | Avg WT: %.2f\n", totalTAT/n, totalWT/n);
}

// -------- FCFS --------
void fcfs(Process p[], int n) {
    // Sort by arrival time
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (p[j].at > p[j+1].at) { Process t=p[j]; p[j]=p[j+1]; p[j+1]=t; }

    int time = 0;
    for (int i = 0; i < n; i++) {
        if (time < p[i].at) time = p[i].at;
        p[i].ct  = time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt  = p[i].tat - p[i].bt;
        time = p[i].ct;
    }
    printResults(p, n, "FCFS");
}

// -------- SJF (Non-Preemptive) --------
void sjf(Process p[], int n) {
    int done[MAX] = {0};
    int time = 0, completed = 0;

    while (completed < n) {
        int idx = -1, minBT = 99999;
        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].at <= time && p[i].bt < minBT) {
                minBT = p[i].bt;
                idx = i;
            }
        }
        if (idx == -1) { time++; continue; }
        time += p[idx].bt;
        p[idx].ct  = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt  = p[idx].tat - p[idx].bt;
        done[idx] = 1;
        completed++;
    }
    printResults(p, n, "SJF (Non-Preemptive)");
}

// -------- SRTF (Preemptive SJF) --------
void srtf(Process p[], int n) {
    int time = 0, completed = 0;
    int done[MAX] = {0};

    while (completed < n) {
        int idx = -1, minR = 99999;
        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].at <= time && p[i].remaining < minR) {
                minR = p[i].remaining;
                idx = i;
            }
        }
        if (idx == -1) { time++; continue; }
        p[idx].remaining--;
        time++;
        if (p[idx].remaining == 0) {
            p[idx].ct  = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt  = p[idx].tat - p[idx].bt;
            done[idx] = 1;
            completed++;
        }
    }
    printResults(p, n, "SRTF (Preemptive SJF)");
}

// -------- Priority (Non-Preemptive, lower number = higher priority) --------
void priority_scheduling(Process p[], int n) {
    int done[MAX] = {0};
    int time = 0, completed = 0;

    while (completed < n) {
        int idx = -1, minP = 99999;
        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].at <= time && p[i].priority < minP) {
                minP = p[i].priority;
                idx = i;
            }
        }
        if (idx == -1) { time++; continue; }
        time += p[idx].bt;
        p[idx].ct  = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt  = p[idx].tat - p[idx].bt;
        done[idx] = 1;
        completed++;
    }
    printResults(p, n, "Priority (Non-Preemptive)");
}

int main() {
    Process p[MAX], copy[MAX];
    int n, choice;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    input(p, n);

    printf("\nSelect Scheduling Algorithm:\n");
    printf("1. FCFS\n2. SJF\n3. SRTF\n4. Priority\n");
    printf("Choice: ");
    scanf("%d", &choice);

    // Copy original data before each run
    memcpy(copy, p, sizeof(Process) * n);

    if      (choice == 1) fcfs(copy, n);
    else if (choice == 2) { memcpy(copy, p, sizeof(Process)*n); sjf(copy, n); }
    else if (choice == 3) { memcpy(copy, p, sizeof(Process)*n); srtf(copy, n); }
    else if (choice == 4) { memcpy(copy, p, sizeof(Process)*n); priority_scheduling(copy, n); }
    else printf("Invalid choice\n");

    return 0;
}

/*
Compile: gcc 08_scheduling.c -o scheduling
Run:     ./scheduling
*/
