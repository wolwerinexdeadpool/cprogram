#include <stdio.h>
#include <stdbool.h>

// Function prototypes
void getInput(int *referenceString, int *totalPages, int *frames);
bool isPageInMemory(int *memoryFrames, int frames, int page);
void addPageToMemory(int *memoryFrames, int frames, int page, int pageFaults);
void printMemoryState(int *memoryFrames, int frames, int pageRequest, int pageFaults);

int main() {
    int totalPages, frames;
    int pageFaults = 0;
    int referenceString[10];
    
    // Get the user input for pages and frames
    getInput(referenceString, &totalPages, &frames);

    int memoryFrames[frames];
    for (int i = 0; i < frames; i++) {
        memoryFrames[i] = -1; // Initialize memory frames to empty
    }

    printf("\n-----------------------------------------\n");
    printf("Page Request | Memory Frame            | Page Faults\n");
    printf("-----------------------------------------\n");

    // Traverse the reference string and simulate the page replacement process
    for (int pageIndex = 0; pageIndex < totalPages; pageIndex++) {
        int pageRequest = referenceString[pageIndex];
        
        // Check if page is in memory
        if (!isPageInMemory(memoryFrames, frames, pageRequest)) {
            pageFaults++;
            addPageToMemory(memoryFrames, frames, pageRequest, pageFaults);
        }

        // Print the current memory state
        printMemoryState(memoryFrames, frames, pageRequest, pageFaults);
    }

    printf("-----------------------------------------\n");
    printf("\nTotal Page Faults: %d\n", pageFaults);
    return 0;
}

// Function to get user input for reference string and frames
void getInput(int *referenceString, int *totalPages, int *frames) {
    printf("\nEnter the number of Pages:\t");
    scanf("%d", totalPages);

    printf("\nEnter reference string values:\n");
    for (int i = 0; i < *totalPages; i++) {
        printf("Reference String [%d]:\t", i + 1);
        scanf("%d", &referenceString[i]);
    }

    printf("\nWhat are the total number of frames:\t");
    scanf("%d", frames);
}

// Function to check if a page is already in memory
bool isPageInMemory(int *memoryFrames, int frames, int page) {
    for (int i = 0; i < frames; i++) {
        if (memoryFrames[i] == page) {
            return true; // Page found in memory
        }
    }
    return false; // Page not found in memory
}

// Function to add a page to memory using FIFO replacement
void addPageToMemory(int *memoryFrames, int frames, int page, int pageFaults) {
    // Check for an empty frame first
    for (int i = 0; i < frames; i++) {
        if (memoryFrames[i] == -1) {
            memoryFrames[i] = page; // Place page in the first available empty frame
            return;
        }
    }
    // If no empty frame is found, replace the oldest page (FIFO)
    memoryFrames[(pageFaults - 1) % frames] = page;
}


// Function to print the current memory state
void printMemoryState(int *memoryFrames, int frames, int pageRequest, int pageFaults) {
    printf("%d\t\t", pageRequest);
    for (int i = 0; i < frames; i++) {
        if (memoryFrames[i] == -1) {
            printf("-\t");
        } else {
            printf("%d\t", memoryFrames[i]);
        }
    }
    printf(" | %s\n", (pageFaults > frames) ? "Page Fault" : "");
}

