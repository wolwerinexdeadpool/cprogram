#include <stdio.h>
#include <stdlib.h>

void inputFiles(int n, int blocks[], int startBlocks[]);
void displayFileTable(int n, int blocks[], int startBlocks[]);
void showFileBlocks(int fileIndex, int blocks[], int startBlocks[]);

int main() {
    int n, fileIndex;
    printf("Enter the number of files: ");
    scanf("%d", &n);

    int blocks[n], startBlocks[n];

    inputFiles(n, blocks, startBlocks);
    displayFileTable(n, blocks, startBlocks);

    printf("Enter file index to view blocks (1 to %d): ", n);
    scanf("%d", &fileIndex);
    showFileBlocks(fileIndex - 1, blocks, startBlocks);

    return 0;
}

void inputFiles(int n, int blocks[], int startBlocks[]) {
    for (int i = 0; i < n; i++) {
        printf("Enter number of blocks occupied by file %d: ", i + 1);
        scanf("%d", &blocks[i]);
        printf("Enter the starting block of file %d: ", i + 1);
        scanf("%d", &startBlocks[i]);
    }
}

void displayFileTable(int n, int blocks[], int startBlocks[]) {
    printf("\nFilename\tStart block\tLength\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\n", i + 1, startBlocks[i], blocks[i]);
    }
}

void showFileBlocks(int fileIndex, int blocks[], int startBlocks[]) {
    printf("Blocks occupied by file %d: ", fileIndex + 1);
    for (int j = 0; j < blocks[fileIndex]; j++) {
        printf("%d ", startBlocks[fileIndex] + j);
    }
    printf("\n");
}

