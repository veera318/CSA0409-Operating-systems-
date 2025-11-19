#include <stdio.h>

#define MAX 50

int main() {
    int disk[MAX], next[MAX];
    int start, last, n, i, current, newBlock;

    // Initialize all disk blocks to free (0)
    for (i = 0; i < MAX; i++) {
        disk[i] = 0;
        next[i] = -1;
    }

    printf("Enter starting block of the file (0–49): ");
    scanf("%d", &start);

    if (disk[start] == 1) {
        printf("Error: Block already allocated.\n");
        return 0;
    }

    disk[start] = 1; 
    current = start;

    printf("Enter number of blocks required for this file: ");
    scanf("%d", &n);

    printf("\nAllocating blocks...\n");

    for (i = 1; i < n; i++) {
        printf("Enter block number to allocate for file block %d: ", i);
        scanf("%d", &newBlock);

        if (newBlock < 0 || newBlock >= MAX) {
            printf("Invalid block. Try again.\n");
            i--;
            continue;
        }

        if (disk[newBlock] == 1) {
            printf("Block already allocated. Choose another.\n");
            i--;
            continue;
        }

        disk[newBlock] = 1;
        next[current] = newBlock;   // Link current block to new block
        current = newBlock;         // Move to next block
    }

    last = current;  // Last allocated block

    // Display structure
    printf("\nDirectory Entry:\n");
    printf("Start Block = %d\n", start);
    printf("Last Block  = %d\n", last);

    printf("\nFile Blocks (Linked Allocation Order):\n");
    current = start;

    while (current != -1) {
        printf("%d -> ", current);
        current = next[current];
    }
    printf("NULL\n");

    return 0;
}

