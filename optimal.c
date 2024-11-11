#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_PAGES 50

// Function prototypes
int isPageInMemory(int memoryFrames[], int frames, int page);
int findOptimalPageToReplace(int memoryFrames[], int frames, int referenceString[], int totalPages, int currentIndex);
void processReferenceString(int frames, int referenceString[], int totalPages, int memoryFrames[], int *pageFaults);
void initializeMemoryFrames(int memoryFrames[], int frames);
void printMemoryState(int memoryFrames[], int frames, int page);

// Function to check if the page is already in memory
int isPageInMemory(int memoryFrames[], int frames, int page) {
    for (int i = 0; i < frames; i++) {
        if (memoryFrames[i] == page) {
            return 1; // Page found in memory
        }
    }
    return 0; // Page not found in memory
}

// Function to find the page to replace using Optimal Replacement
int findOptimalPageToReplace(int memoryFrames[], int frames, int referenceString[], int totalPages, int currentIndex) {
    int farthestIndex = -1, pageToReplace = -1;

    // Check future references for each page in memory
    for (int i = 0; i < frames; i++) {
        int nextUse = -1;
        // Find when the page at memoryFrames[i] is used next
        for (int j = currentIndex + 1; j < totalPages; j++) {
            if (referenceString[j] == memoryFrames[i]) {
                nextUse = j;
                break;
            }
        }

        // If the page won't be used again, choose it immediately for replacement
        if (nextUse == -1) {
            return i; // No future use found, replace this page
        }

        // Track the page used farthest in the future
        if (nextUse > farthestIndex) {
            farthestIndex = nextUse;
            pageToReplace = i;
        }
    }
    return pageToReplace;
}

// Function to initialize memory frames to empty
void initializeMemoryFrames(int memoryFrames[], int frames) {
    for (int i = 0; i < frames; i++) {
        memoryFrames[i] = -1; // Set each frame to -1 (indicating empty)
    }
}

// Function to print the current state of memory frames
void printMemoryState(int memoryFrames[], int frames, int page) {
    printf("\nPage %d -> Frames: ", page);
    for (int i = 0; i < frames; i++) {
        if (memoryFrames[i] == -1) {
            printf(" - ");
        } else {
            printf(" %d ", memoryFrames[i]);
        }
    }
}

// Function to process the reference string and implement Optimal Page Replacement
void processReferenceString(int frames, int referenceString[], int totalPages, int memoryFrames[], int *pageFaults) {
    for (int i = 0; i < totalPages; i++) {
        int page = referenceString[i];

        // Step 1: Check if page is already in memory
        if (!isPageInMemory(memoryFrames, frames, page)) {
            (*pageFaults)++;  // Increment page faults count

            // Step 2: Find an empty frame or select a page to replace
            int replaceIndex = -1;
            for (int j = 0; j < frames; j++) {
                if (memoryFrames[j] == -1) { // Look for an empty frame
                    replaceIndex = j;
                    break;
                }
            }

            // Step 3: If memory is full, find the optimal page to replace
            if (replaceIndex == -1) {
                replaceIndex = findOptimalPageToReplace(memoryFrames, frames, referenceString, totalPages, i);
            }

            // Step 4: Replace the selected page with the current page
            memoryFrames[replaceIndex] = page;
        }

        // Print the current memory state after processing this page
        printMemoryState(memoryFrames, frames, page);
    }
}

int main() {
    int frames, totalPages, pageFaults = 0;
    int memoryFrames[MAX_FRAMES];  // Array to hold pages in memory
    int referenceString[MAX_PAGES]; // Reference string of pages

    // Step 1: Input number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    // Step 2: Input reference string
    printf("Enter the number of pages in reference string: ");
    scanf("%d", &totalPages);
    printf("Enter the reference string:\n");
    for (int i = 0; i < totalPages; i++) {
        scanf("%d", &referenceString[i]);
    }

    // Step 3: Initialize memory frames
    initializeMemoryFrames(memoryFrames, frames);

    // Step 4: Process the reference string
    processReferenceString(frames, referenceString, totalPages, memoryFrames, &pageFaults);

    // Output total page faults
    printf("\n\nTotal Page Faults: %d\n", pageFaults);

    return 0;
}

