#include <stdio.h>

int main() {
    int pages[50], frames[10];
    int n, f;
    int i, j, k, flag, faults = 0;
    int front = 0; // FIFO pointer

    // Input
    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    // Initialize frames to empty
    for (i = 0; i < f; i++)
        frames[i] = -1;

    // FIFO Page Replacement Logic
    printf("\nFrame Status:\n");

    for (i = 0; i < n; i++) {
        flag = 0;

        // Check if page is already present
        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                flag = 1; // page hit
                break;
            }
        }

        // If miss, replace page using FIFO
        if (flag == 0) {
            frames[front] = pages[i];
            front = (front + 1) % f; // move FIFO pointer
            faults++;
        }

        // Print frames
        for (k = 0; k < f; k++) {
            if (frames[k] == -1)
                printf("- ");
            else
                printf("%d ", frames[k]);
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);

    return 0;
}

