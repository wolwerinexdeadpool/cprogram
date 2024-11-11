#include <stdio.h>

int main() {
    int blockSizes[20], processSizes[20], blockAllocated[20], fragmentation[20];
    int numBlocks, numProcesses;
    int i, j, temp;
    static int blockOccupied[20], processBlock[20];
    
    printf("Memory Management Scheme - Best Fit\n");
    printf("Enter the number of blocks: ");
    scanf("%d", &numBlocks);
    printf("Enter the number of processes: ");
    scanf("%d", &numProcesses);
    
    int smallestFragmentation = 9999; // Initial high value for comparison

    // Read block sizes
    printf("Enter the size of each block:\n");
    for (i = 0; i < numBlocks; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSizes[i]);
        blockOccupied[i] = 0; // Initialize all blocks as unoccupied
    }

    // Read process sizes
    printf("Enter the size of each process:\n");
    for (i = 0; i < numProcesses; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSizes[i]);
    }

    // Best Fit allocation
    for (i = 0; i < numProcesses; i++) {
        smallestFragmentation = 9999; // Reset for each process

        for (j = 0; j < numBlocks; j++) {
            if (!blockOccupied[j]) { // Check if block is unoccupied
                temp = blockSizes[j] - processSizes[i];
                if (temp >= 0 && temp < smallestFragmentation) { // Fits and is the smallest leftover
                    processBlock[i] = j;
                    smallestFragmentation = temp;
                }
            }
        }

        // If a block was found for the process
        if (smallestFragmentation != 9999) {
            blockOccupied[processBlock[i]] = 1; // Mark block as occupied
            fragmentation[i] = smallestFragmentation; // Store the leftover space (fragmentation)
        } else {
            processBlock[i] = -1; // No block found for this process
        }
    }

    // Display results
    printf("\nProcess No.\tProcess Size\tBlock No.\tBlock Size\tFragmentation");
    for (i = 0; i < numProcesses; i++) {
        if (processBlock[i] != -1) {
            printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", 
                    i + 1, processSizes[i], processBlock[i] + 1, 
                    blockSizes[processBlock[i]], fragmentation[i]);
        } else {
            printf("\n%d\t\t%d\t\tNot Allocated", i + 1, processSizes[i]);
        }
    }
    printf("\n");

    return 0;
}

