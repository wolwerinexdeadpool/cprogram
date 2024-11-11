#include <stdio.h>

int main() {
    int blockSizes[10], processSizes[10], numBlocks, numProcesses;
    int isBlockAllocated[10], allocatedProcessIndex[10];
    int i, j;

    printf("\n\tMemory Management Scheme - First Fit\n");

    // Initialize allocation flags and process allocations
    for (i = 0; i < 10; i++) {
        isBlockAllocated[i] = 0;             // 0 means block is free
        allocatedProcessIndex[i] = -1;       // -1 means no process is allocated to the block
    }

    // Input number of memory blocks
    printf("Enter number of memory blocks: ");
    scanf("%d", &numBlocks);

    // Input size of each memory block
    printf("Enter the size of each memory block:\n");
    for (i = 0; i < numBlocks; i++) {
        printf("Size of Block %d: ", i + 1);
        scanf("%d", &blockSizes[i]);
    }

    // Input number of processes
    printf("Enter number of processes: ");
    scanf("%d", &numProcesses);

    // Input size of each process
    printf("Enter the size of each process:\n");
    for (i = 0; i < numProcesses; i++) {
        printf("Size of Process %d: ", i + 1);
        scanf("%d", &processSizes[i]);
    }

    // First Fit allocation logic
    for (i = 0; i < numProcesses; i++) {         // Loop through each process
        for (j = 0; j < numBlocks; j++) {        // Find the first available block
            if (isBlockAllocated[j] == 0 && blockSizes[j] >= processSizes[i]) { 
                allocatedProcessIndex[j] = i;    // Allocate the process to this block
                isBlockAllocated[j] = 1;         // Mark the block as allocated
                break;                           // Move to the next process
            }
        }
    }
//allocatedProcessIndex is the block in which we store process index which has been allocatewd to it
    // Display the allocation result
    printf("\nBlock No.\tBlock Size\tProcess No.\tProcess Size\n");
    for (i = 0; i < numBlocks; i++) {
        printf("%d\t\t%d\t\t", i + 1, blockSizes[i]);
        if (isBlockAllocated[i] == 1) {
            printf("%d\t\t\t%d", allocatedProcessIndex[i] + 1, processSizes[allocatedProcessIndex[i]]);
        } else {
            printf("Not allocated");
        }
        printf("\n");
    }

    return 0;
}

