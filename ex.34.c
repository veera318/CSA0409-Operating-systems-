#include <stdio.h>

#define MAX 50

int main() {
    int disk[MAX], start, length, i, j, choice;
    
    // Initially all disk blocks are free (0 = free, 1 = allocated)
    for (i = 0; i < MAX; i++)
        disk[i] = 0;
    
    while (1) {
        printf("\n1. Allocate File");
        printf("\n2. Access Record");
        printf("\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            
        case 1:
            printf("Enter starting block (0–49): ");
            scanf("%d", &start);
            printf("Enter number of records: ");
            scanf("%d", &length);
            
            // Check bounds
            if (start + length > MAX) {
                printf("Allocation failed: exceeds disk size.\n");
                break;
            }
            
            // Check if all required blocks are free
            for (i = start; i < start + length; i++) {
                if (disk[i] == 1) {
                    printf("Allocation failed: block %d already allocated.\n", i);
                    break;
                }
            }
            
            // If all blocks free, allocate sequentially
            if (i == start + length) {
                for (j = start; j < start + length; j++)
                    disk[j] = 1;
                printf("File allocated from block %d to %d\n",
                       start, start + length - 1);
            }
            break;
            
        case 2:
            printf("Enter starting block of file: ");
            scanf("%d", &start);
            
            printf("Enter record number to access (1,2,3...): ");
            scanf("%d", &length);
            
            printf("Sequential Access:\n");
            for (i = 0; i < length; i++) {
                printf("Reading block %d\n", start + i);
                if (disk[start + i] == 0) {
                    printf("Error: block %d not allocated (incomplete file).\n",
                           start + i);
                    break;
                }
            }
            break;
            
        case 3:
            return 0;
            
        default:
            printf("Invalid choice.\n");
        }
    }
    
    return 0;
}

