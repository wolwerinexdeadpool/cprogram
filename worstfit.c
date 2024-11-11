#include <stdio.h>

int main() {
    int numBlocks, numFiles;
    int blockSize[10], fileSize[10], frag[10]; 
    int allocatedBlock[10], blockAssigned[10] = {0}; // Initial assignment for all blocks is unallocated (0)
    
    printf("\n\t\t\tMemory Management Scheme - Worst Fit\n");
    
    // Input the number of blocks and files
    printf("Enter the Total Number of Blocks: ");
    scanf("%d", &numBlocks);
    printf("Enter the Total Number of Files: ");
    scanf("%d", &numFiles);
    
    // Input sizes of each memory block
    printf("\nEnter the Size of the Blocks:\n");
    for (int i = 0; i < numBlocks; i++) {
        printf("Block No.%d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }
    
    // Input sizes of each file
    printf("\nEnter the Size of the Files:\n");
    for (int i = 0; i < numFiles; i++) {
        printf("File No.%d: ", i + 1);
        scanf("%d", &fileSize[i]);
    }
    
    // Allocate files to blocks using the Worst Fit strategy
    for (int i = 0; i < numFiles; i++) {
        int worstFitIndex = -1;
        int maxFragment = -1;

        for (int j = 0; j < numBlocks; j++) {
            if (!blockAssigned[j]) { // Block is free
                int fragment = blockSize[j] - fileSize[i];
                
                // Check if the block is large enough and has more space than the current worst fit
                if (fragment >= 0 && fragment > maxFragment) {
                    worstFitIndex = j;
                    maxFragment = fragment;
                }
            }
        }
        
        if (worstFitIndex != -1) {
            allocatedBlock[i] = worstFitIndex;
            frag[i] = maxFragment;
            blockAssigned[worstFitIndex] = 1; // Mark the block as allocated
        } else {
            allocatedBlock[i] = -1; // No suitable block found
            frag[i] = 0;
        }
    }
    
    // Display results
    printf("\nFile Number\tFile Size\tBlock Number\tBlock Size\tFragment\n");
    for (int i = 0; i < numFiles; i++) {
        if (allocatedBlock[i] != -1) {
            int blockIdx = allocatedBlock[i];
            printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", 
                   i + 1, fileSize[i], blockIdx + 1, blockSize[blockIdx], frag[i]);
        } else {
            printf("%d\t\t%d\t\tNot Allocated\n", i + 1, fileSize[i]);
        }
    }
    return 0;
}

