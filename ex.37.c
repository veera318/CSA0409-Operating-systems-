#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, i;
    int req[50];
    int total_movement = 0;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    printf("Enter the disk request sequence:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("\nFCFS Disk Scheduling\n");
    printf("Head movement order: %d", head);

    for (i = 0; i < n; i++) {
        total_movement += abs(req[i] - head);
        head = req[i];
        printf(" -> %d", head);
    }

    printf("\n\nTotal Head Movement = %d cylinders\n", total_movement);

    return 0;
}

