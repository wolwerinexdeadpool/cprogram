#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_PAGES 20

// Function prototypes
void initializeMemoryFrames(int memoryFrames[], int numFrames);
int isPageInMemory(int page, int memoryFrames[], int numFrames);
int findEmptyFrame(int memoryFrames[], int numFrames);
int findLeastRecentlyUsedIndex(int memoryFrames[], int referenceString[], int numFrames, int currentIndex);
void addPageToMemory(int page, int memoryFrames[], int referenceString[], int numFrames, int currentIndex);
void displayMemoryFrames(int memoryFrames[], int numFrames);

int main() {
    int referenceString[MAX_PAGES], memoryFrames[MAX_FRAMES];
    int numPages, numFrames, pageFaults = 0;

    // Input number of pages
    printf("Enter the number of pages: ");
    scanf("%d", &numPages);

    // Input reference string
    printf("Enter the reference string:\n");
    for (int i = 0; i < numPages; i++) {
        scanf("%d", &referenceString[i]);
    }

    // Input number of frames
    printf("Enter the number of frames: ");
    scanf("%d", &numFrames);

    // Initialize memory frames
    initializeMemoryFrames(memoryFrames, numFrames);

    // Process each page in the reference string
    for (int i = 0; i < numPages; i++) {
        int currentPage = referenceString[i];

        // Check if the page is already in memory
        if (!isPageInMemory(currentPage, memoryFrames, numFrames)) {
            pageFaults++;  // Page fault occurs
            addPageToMemory(currentPage, memoryFrames, referenceString, numFrames, i);
        }

        // Display memory state after each page request
        printf("Page %d: ", currentPage);
        displayMemoryFrames(memoryFrames, numFrames);
    }

    printf("\nTotal page faults: %d\n", pageFaults);
    return 0;
}

// Function to initialize memory frames to -1 (empty)
void initializeMemoryFrames(int memoryFrames[], int numFrames) {
    for (int i = 0; i < numFrames; i++) {
        memoryFrames[i] = -1;
    }
}

// Function to check if the page is already in memory
int isPageInMemory(int page, int memoryFrames[], int numFrames) {
    for (int i = 0; i < numFrames; i++) {
        if (memoryFrames[i] == page) {
            return 1; // Page found in memory
        }
    }
    return 0; // Page not found in memory
}

// Function to find the index of an empty frame in memory
int findEmptyFrame(int memoryFrames[], int numFrames) {
    for (int i = 0; i < numFrames; i++) {
        if (memoryFrames[i] == -1) {
            return i; // Return index of the first empty frame
        }
    }
    return -1; // No empty frames available
}

// Function to find the least recently used page in memory
int findLeastRecentlyUsedIndex(int memoryFrames[], int referenceString[], int numFrames, int currentIndex) {
    int leastRecentlyUsedIndex = -1, farthest = currentIndex;

    for (int i = 0; i < numFrames; i++) {
        int j;

        // Look back in the reference string to find when the current frame's page was last used
        for (j = currentIndex - 1; j >= 0; j--) {
            if (memoryFrames[i] == referenceString[j]) {
                if (j < farthest) {
                    farthest = j;
                    leastRecentlyUsedIndex = i;
                }
                break;
            }
        }

        // If a page in the frame was not used at all in the past, select it immediately
        if (j == -1) {
            return i;
        }
    }
    return leastRecentlyUsedIndex;
}

// Function to add a page to memory, either by finding an empty frame or replacing the least recently used page
void addPageToMemory(int page, int memoryFrames[], int referenceString[], int numFrames, int currentIndex) {
    int emptyFrame = findEmptyFrame(memoryFrames, numFrames);
    if (emptyFrame != -1) {
        memoryFrames[emptyFrame] = page; // Place the page in the empty frame
    } else {
        int lruIndex = findLeastRecentlyUsedIndex(memoryFrames, referenceString, numFrames, currentIndex);
        memoryFrames[lruIndex] = page; // Replace the least recently used page
    }
}

// Function to display the current state of memory frames
void displayMemoryFrames(int memoryFrames[], int numFrames) {
    for (int i = 0; i < numFrames; i++) {
        if (memoryFrames[i] != -1) {
            printf("%d\t", memoryFrames[i]);
        } else {
            printf("-\t"); // Empty frame
        }
    }
    printf("\n");
}

