#include <stdio.h>

#define MAX 50

int main() {
    int disk[MAX], indexBlock, fileSize;
    int indexTable[MAX];
    int i, block;

    // Initialize disk (0 = free, 1 = allocated)
    for (i = 0; i < MAX; i++)
        disk[i] = 0;

    printf("Enter the index block number (0–49): ");
    scanf("%d", &indexBlock);

    // Check if index block is free
    if (disk[indexBlock] == 1) {
        printf("Index block already allocated. Try another.\n");
        return 0;
    }

    disk[indexBlock] = 1;  // allocate index block

    printf("Enter number of blocks needed for the file: ");
    scanf("%d", &fileSize);

    printf("\nAllocating blocks...\n");

    for (i = 0; i < fileSize; i++) {
        printf("Enter block number for file block %d: ", i);
        scanf("%d", &block);

        // Check if valid and free
        if (block < 0 || block >= MAX) {
            printf("Invalid block number.\n");
            i--;
            continue;
        }
        if (disk[block] == 1) {
            printf("Block already allocated. Choose another.\n");
            i--;
            continue;
        }

        disk[block] = 1;
        indexTable[i] = block;
    }

    // Display mapping
    printf("\nFile Allocation Using Indexed Strategy:\n");
    printf("Index Block: %d\n", indexBlock);
    printf("Block Mappings:\n");

    for (i = 0; i < fileSize; i++)
        printf("Index[%d] -> Block %d\n", i, indexTable[i]);

    // Accessing file blocks
    printf("\nAccessing file:\n");
    for (i = 0; i < fileSize; i++)
        printf("Reading block %d\n", indexTable[i]);

    return 0;
}

