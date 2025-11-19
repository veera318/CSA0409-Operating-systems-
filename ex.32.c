#include <stdio.h>

int findLRU(int time[], int f) {
    int i, min = time[0], pos = 0;
    for (i = 1; i < f; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int main() {
    int pages[50], frames[10], time[10];
    int n, f;
    int i, j, k, pos, flag1, flag2, faults = 0;
    int counter = 0;

    // Input
    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    // Initialize frames
    for (i = 0; i < f; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    printf("\nFrame Status:\n");

    for (i = 0; i < n; i++) {
        flag1 = flag2 = 0;

        // Check if page already exists (Hit)
        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                counter++;
                time[j] = counter;
                flag1 = flag2 = 1;
                break;
            }
        }

        // Page not found ? Insert
        if (flag1 == 0) {
            for (j = 0; j < f; j++) {
                if (frames[j] == -1) {  // empty frame
                    counter++;
                    faults++;
                    frames[j] = pages[i];
                    time[j] = counter;
                    flag2 = 1;
                    break;
                }
            }
        }

        // No empty frame ? Replace LRU
        if (flag2 == 0) {
            pos = findLRU(time, f);
            counter++;
            faults++;
            frames[pos] = pages[i];
            time[pos] = counter;
        }

        // Print frame table
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

