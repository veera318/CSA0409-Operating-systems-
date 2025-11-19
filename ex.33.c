#include <stdio.h>

int findOptimal(int pages[], int frames[], int n, int f, int index) {
    int farthest = -1, pos = -1;

    for (int i = 0; i < f; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frames[i] == pages[j]) { // Page will be used again
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }

        // If a page is never used again, replace it immediately
        if (j == n)
            return i;
    }

    // If all pages will be used again, replace the farthest one
    return pos == -1 ? 0 : pos;
}

int main() {
    int pages[50], frames[10];
    int n, f, faults = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter page reference string:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    // Initialize frames
    for (int i = 0; i < f; i++)
        frames[i] = -1;

    printf("\nFrame Status:\n");

    for (int i = 0; i < n; i++) {
        int flag = 0;

        // Check if page already exists (HIT)
        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                flag = 1;
                break;
            }
        }

        // MISS ? Handle replacement
        if (flag == 0) {
            faults++;

            // Empty frame exists
            int empty = -1;
            for (int j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    empty = j;
                    break;
                }
            }

            if (empty != -1) {
                frames[empty] = pages[i];
            } else {
                // Optimal replacement
                int pos = findOptimal(pages, frames, n, f, i + 1);
                frames[pos] = pages[i];
            }
        }

        // Print frame status
        for (int k = 0; k < f; k++) {
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

