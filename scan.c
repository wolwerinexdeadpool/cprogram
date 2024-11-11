#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void sortRequests(int requests[], int numRequests);
int findStartingIndex(int requests[], int numRequests, int headPosition);
int calculateTotalHeadMovement_SCAN(int requests[], int numRequests, int headPosition, int diskSize, int direction);

// Function to manually sort the requests array in ascending order
void sortRequests(int requests[], int numRequests) {
    for (int i = 0; i < numRequests - 1; i++) {
        for (int j = i + 1; j < numRequests; j++) {
            if (requests[i] > requests[j]) {
                int temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }
        }
    }
}

// Function to find the starting index based on the head position
int findStartingIndex(int requests[], int numRequests, int headPosition) {
    for (int i = 0; i < numRequests; i++) {
        if (requests[i] >= headPosition) {
            return i;
        }
    }
    return numRequests - 1;
}

// Function to calculate total head movement for SCAN
int calculateTotalHeadMovement_SCAN(int requests[], int numRequests, int headPosition, int diskSize, int direction) {
    int totalMovement = 0;
    sortRequests(requests, numRequests);
    int startIndex = findStartingIndex(requests, numRequests, headPosition);

    if (direction == 1) { // Moving towards high end
        for (int i = startIndex; i < numRequests; i++) {
            totalMovement += abs(requests[i] - headPosition);
            headPosition = requests[i];
        }
        totalMovement += abs(diskSize - 1 - headPosition);
        headPosition = diskSize - 1;
        
        for (int i = startIndex - 1; i >= 0; i--) {
            totalMovement += abs(requests[i] - headPosition);
            headPosition = requests[i];
        }
    } else { // Moving towards low end
        for (int i = startIndex - 1; i >= 0; i--) {
            totalMovement += abs(requests[i] - headPosition);
            headPosition = requests[i];
        }
        totalMovement += abs(headPosition);
        headPosition = 0;
        
        for (int i = startIndex; i < numRequests; i++) {
            totalMovement += abs(requests[i] - headPosition);
            headPosition = requests[i];
        }
    }
    return totalMovement;
}

int main() {
    int requests[] = {95, 180, 34, 119, 11, 123, 62, 64};
    int numRequests = sizeof(requests) / sizeof(requests[0]);
    int headPosition, diskSize, direction;

    printf("Enter the initial head position: ");
    scanf("%d", &headPosition);
    printf("Enter the total disk size: ");
    scanf("%d", &diskSize);
    printf("Enter head movement direction (1 for high, 0 for low): ");
    scanf("%d", &direction);

    int totalHeadMovement = calculateTotalHeadMovement_SCAN(requests, numRequests, headPosition, diskSize, direction);
    printf("Total head movement for SCAN: %d\n", totalHeadMovement);

    return 0;
}

