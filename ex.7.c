#include <stdio.h>

struct Process {
    int pid, arrival, burst, waiting, turnaround, completed;
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
        p[i].completed = 0;
    }

    int total_wt = 0, total_tt = 0;

    while (completed < n) {
        int idx = -1, min_burst = 1e9;

        for (int i = 0; i < n; i++)
            if (p[i].arrival <= time && !p[i].completed)
                if (p[i].burst < min_burst) {
                    min_burst = p[i].burst;
                    idx = i;
                }

        if (idx != -1) {
            p[idx].waiting = (time - p[idx].arrival > 0) ? time - p[idx].arrival : 0;
            time += p[idx].burst;
            p[idx].turnaround = p[idx].waiting + p[idx].burst;
            p[idx].completed = 1;

            total_wt += p[idx].waiting;
            total_tt += p[idx].turnaround;
            completed++;
        } else time++;
    }

    printf("\nP\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival, p[i].burst, p[i].waiting, p[i].turnaround);

    printf("\nAverage Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tt / n);

    return 0;
}

