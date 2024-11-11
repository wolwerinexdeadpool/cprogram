#include <stdio.h>

struct IndexedFile {
    int indexBlock;
    int size;
    int blocks[10];
};

void inputIndexedFiles(int n, struct IndexedFile files[]);
void displayIndexedFiles(int n, struct IndexedFile files[]);

int main() {
    int n;
    printf("Enter number of files: ");
    scanf("%d", &n);

    struct IndexedFile files[n];
    inputIndexedFiles(n, files);
    displayIndexedFiles(n, files);

    return 0;
}

void inputIndexedFiles(int n, struct IndexedFile files[]) {
    for (int i = 0; i < n; i++) {
        printf("Enter index block for file %d: ", i + 1);
        scanf("%d", &files[i].indexBlock);
        printf("Enter number of blocks occupied by file %d: ", i + 1);
        scanf("%d", &files[i].size);
        printf("Enter block numbers for file %d: ", i + 1);
        for (int j = 0; j < files[i].size; j++) {
            scanf("%d", &files[i].blocks[j]);
        }
    }
}

void displayIndexedFiles(int n, struct IndexedFile files[]) {
    printf("\nFile\tIndex\tBlocks\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t", i + 1, files[i].indexBlock);
        for (int j = 0; j < files[i].size; j++) {
            if (j < files[i].size - 1) {
                printf("%d--->", files[i].blocks[j]);
            } else {
                printf("%d", files[i].blocks[j]);
            }
        }
        printf("\n");
    }
}

