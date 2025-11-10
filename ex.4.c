#include <stdio.h>

struct Process {
    int pid;          // Process ID
    int burst_time;   // Execution time
    int waiting_time;
    int turnaround_time;
};

void sortByBurstTime(struct Process p[], int n) {
    // Simple bubble sort to arrange processes by burst time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].burst_time > p[j + 1].burst_time) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void calculateTimes(struct Process p[], int n) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    p[0].waiting_time = 0; // First process has no waiting time

    // Calculate waiting time for each process
    for (int i = 1; i < n; i++) {
        p[i].waiting_time = 0;
        for (int j = 0; j < i; j++)
            p[i].waiting_time += p[j].burst_time;
    }

    // Calculate turnaround time for each process
    for (int i = 0; i < n; i++)
        p[i].turnaround_time = p[i].burst_time + p[i].waiting_time;

    // Print and calculate averages
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        total_waiting_time += p[i].waiting_time;
        total_turnaround_time += p[i].turnaround_time;
        printf("P%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].burst_time,
               p[i].waiting_time, p[i].turnaround_time);
    }

    printf("\nAverage Waiting Time: %.2f", (float)total_waiting_time / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter burst time for Process P%d: ", i + 1);
        scanf("%d", &p[i].burst_time);
    }

    // Sort processes based on burst time
    sortByBurstTime(p, n);

    printf("\nProcesses scheduled in order of shortest execution time:\n");
    for (int i = 0; i < n; i++) {
        printf("P%d ", p[i].pid);
    }

    calculateTimes(p, n);

    return 0;
}

