#include <stdio.h>

struct Process {
    int pid, arrival, burst, remaining, waiting, turnaround;
};

int main() {
    int n, time = 0, quantum;
    printf("Number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Arrival time for P%d: ", i + 1);
        scanf("%d", &p[i].arrival);
        printf("Burst time for P%d: ", i + 1);
        scanf("%d", &p[i].burst);
        p[i].remaining = p[i].burst;
        p[i].waiting = p[i].turnaround = 0;
    }

    printf("Time quantum: ");
    scanf("%d", &quantum);

    int completed = 0, total_wt = 0, total_tt = 0;

    while (completed < n) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0) {
                done = 0;
                if (p[i].remaining > quantum) {
                    time += quantum;
                    p[i].remaining -= quantum;
                } else {
                    time += p[i].remaining;
                    p[i].waiting = time - p[i].arrival - p[i].burst;
                    p[i].turnaround = p[i].waiting + p[i].burst;
                    total_wt += p[i].waiting;
                    total_tt += p[i].turnaround;
                    p[i].remaining = 0;
                    completed++;
                }
            }
        }
        if (done) time++; // No process ready, advance time
    }

    printf("\nP\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival, p[i].burst, p[i].waiting, p[i].turnaround);

    printf("\nAverage Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tt / n);

    return 0;
}

