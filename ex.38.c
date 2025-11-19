#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++)
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

int main() {
    int req[100], left[100], right[100];
    int n, i, j = 0, k = 0;
    int head, disk_size, move;
    int total_movement = 0;

    printf("Enter number of disk requests: ");
    scanf("%d", &n);

    printf("Enter disk request sequence:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size (last cylinder number): ");
    scanf("%d", &disk_size);

    printf("Enter head movement direction (1 = right, 0 = left): ");
    scanf("%d", &move);

    // Divide into left and right groups
    for (i = 0; i < n; i++) {
        if (req[i] < head)
            left[j++] = req[i];
        else
            right[k++] = req[i];
    }

    // Sort both groups
    sort(left, j);
    sort(right, k);

    printf("\nSCAN Disk Scheduling Order:\n");
    printf("%d", head);

    if (move == 1) {
        // Move right first
        for (i = 0; i < k; i++) {
            total_movement += abs(head - right[i]);
            head = right[i];
            printf(" -> %d", head);
        }

        // Go to last cylinder
        total_movement += abs(head - (disk_size - 1));
        head = disk_size - 1;
        printf(" -> %d", head);

        // Now move left
        for (i = j - 1; i >= 0; i--) {
            total_movement += abs(head - left[i]);
            head = left[i];
            printf(" -> %d", head);
        }

    } else {
        // Move left first
        for (i = j - 1; i >= 0; i--) {
            total_movement += abs(head - left[i]);
            head = left[i];
            printf(" -> %d", head);
        }

        // Go to cylinder 0
        total_movement += abs(head - 0);
        head = 0;
        printf(" -> %d", head);

        // Move right
        for (i = 0; i < k; i++) {
            total_movement += abs(head - right[i]);
            head = right[i];
            printf(" -> %d", head);
        }
    }

    printf("\n\nTotal Head Movement = %d cylinders\n", total_movement);

    return 0;
}

