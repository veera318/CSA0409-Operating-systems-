#include <stdio.h>

struct Process {
    int pid;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
};

void sortByPriority(struct Process p[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (p[j].priority < p[j + 1].priority) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
}

int main() {
    int n;
    printf("Number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Burst time for P%d: ", i + 1);
        scanf("%d", &p[i].burst_time);
        printf("Priority for P%d: ", i + 1);
        scanf("%d", &p[i].priority);
    }

    sortByPriority(p, n);

    p[0].waiting_time = 0;
    for (int i = 1; i < n; i++) {
        p[i].waiting_time = 0;
        for (int j = 0; j < i; j++)
            p[i].waiting_time += p[j].burst_time;
    }

    int total_wt = 0, total_tt = 0;
    printf("\nP\tPriority\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        p[i].turnaround_time = p[i].burst_time + p[i].waiting_time;
        total_wt += p[i].waiting_time;
        total_tt += p[i].turnaround_time;
        printf("P%d\t%d\t\t%d\t%d\t%d\n", p[i].pid, p[i].priority, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time);
    }

    printf("Average Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tt / n);

    return 0;
}

