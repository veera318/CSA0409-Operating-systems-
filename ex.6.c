#include <stdio.h>

struct Process {
    int pid, arrival, burst, remaining, priority, waiting, turnaround;
};

int main() {
    int n, completed = 0, time = 0;
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
        printf("Priority for P%d: ", i + 1);
        scanf("%d", &p[i].priority);
    }

    int total_wt = 0, total_tt = 0;

    while (completed < n) {
        int idx = -1, high = -1;
        for (int i = 0; i < n; i++)
            if (p[i].arrival <= time && p[i].remaining > 0)
                if (p[i].priority > high || (p[i].priority == high && p[i].arrival < p[idx].arrival)) {
                    high = p[i].priority;
                    idx = i;
                }

        if (idx != -1) {
            p[idx].remaining--;
            time++;
            if (p[idx].remaining == 0) {
                completed++;
                p[idx].turnaround = time - p[idx].arrival;
                p[idx].waiting = p[idx].turnaround - p[idx].burst;
                total_wt += p[idx].waiting;
                total_tt += p[idx].turnaround;
            }
        } else time++;
    }

    printf("\nP\tArrival\tBurst\tPriority\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\n", p[i].pid, p[i].arrival, p[i].burst, p[i].priority, p[i].waiting, p[i].turnaround);

    printf("\nAverage Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tt / n);

    return 0;
}

