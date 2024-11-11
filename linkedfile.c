#include <stdio.h>

struct File {
    char name[10];
    int start, size;
    int blocks[10];
};

void inputLinkedFiles(int n, struct File files[]);
void displayLinkedFiles(int n, struct File files[]);

int main() {
    int n;
    printf("Enter number of files: ");
    scanf("%d", &n);

    struct File files[n];
    inputLinkedFiles(n, files);
    displayLinkedFiles(n, files);

    return 0;
}

void inputLinkedFiles(int n, struct File files[]) {
    for (int i = 0; i < n; i++) {
        printf("Enter file name: ");
        scanf("%s", files[i].name);
        printf("Enter starting block: ");
        scanf("%d", &files[i].start);
        files[i].blocks[0] = files[i].start;
        printf("Enter number of blocks: ");
        scanf("%d", &files[i].size);
        printf("Enter block numbers: ");
        for (int j = 1; j <= files[i].size; j++) {
            scanf("%d", &files[i].blocks[j]);
        }
    }
}

void displayLinkedFiles(int n, struct File files[]) {
    printf("\nFile\tStart\tSize\tBlocks\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t%d\t", files[i].name, files[i].start, files[i].size);
        for (int j = 1; j <= files[i].size; j++) {
            if (j < files[i].size) {
                printf("%d--->", files[i].blocks[j]);
            } else {
                printf("%d", files[i].blocks[j]);
            }
        }
        printf("\n");
    }
}

