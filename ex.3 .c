#include <stdio.h>

struct Process {
    int id;
    int burst_time;
    int waiting_time;
    int turn_around_time;
};

void calculateWaitingTime(struct Process proc[], int n) {
    proc[0].waiting_time = 0;
    for (int i = 1; i < n; i++) {
        proc[i].waiting_time = proc[i-1].waiting_time + proc[i-1].burst_time;
    }
}

void calculateTurnAroundTime(struct Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turn_around_time = proc[i].burst_time + proc[i].waiting_time;
    }
}

void findAverageTime(struct Process proc[], int n) {
    int total_waiting_time = 0, total_turn_around_time = 0;

    for (int i = 0; i < n; i++) {
        total_waiting_time += proc[i].waiting_time;
        total_turn_around_time += proc[i].turn_around_time;
    }

    printf("Average waiting time: %.2f\n", (float)total_waiting_time / n);
    printf("Average turnaround time: %.2f\n", (float)total_turn_around_time / n);
}

int main() {
    struct Process proc[] = {
        {1, 10},
        {2, 5},
        {3, 8}
    };
    int n = sizeof(proc) / sizeof(proc[0]);

    calculateWaitingTime(proc, n);
    calculateTurnAroundTime(proc, n);
    findAverageTime(proc, n);

    return 0;
}

