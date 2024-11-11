#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function Prototypes
void inputRequests(int RQ[], int *n);
int findClosestTrack(int RQ[], int n, int headPosition, int *visited);
int calculateTotalHeadMovement(int RQ[], int n, int initialHeadPosition);

int main() {
    int RQ[100], n, initialHeadPosition, totalHeadMovement;

    // Input the number of requests and the sequence of requests
    inputRequests(RQ, &n);

    // Input the initial position of the disk head
    printf("Enter initial head position: ");
    scanf("%d", &initialHeadPosition);

    // Calculate the total head movement using SSTF disk scheduling algorithm
    totalHeadMovement = calculateTotalHeadMovement(RQ, n, initialHeadPosition);

    // Output the result
    printf("Total head movement is %d\n", totalHeadMovement);

    return 0;
}

// Function to input the request sequence and number of requests
void inputRequests(int RQ[], int *n) {
    printf("Enter the number of Requests: ");
    scanf("%d", n);

    printf("Enter the Requests sequence:\n");
    for (int i = 0; i < *n; i++) {
        scanf("%d", &RQ[i]);
    }
}

// Function to find the closest unvisited track to the current head position
int findClosestTrack(int RQ[], int n, int headPosition, int *visited) {
    int minDistance = INT_MAX;
    int closestIndex = -1;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) { // Check if the request has not been serviced
            int distance = abs(RQ[i] - headPosition);
            if (distance < minDistance) {
                minDistance = distance;
                closestIndex = i;
            }
        }
    }

    return closestIndex;
}

// Function to calculate the total head movement using SSTF scheduling
int calculateTotalHeadMovement(int RQ[], int n, int initialHeadPosition) {
    int totalHeadMovement = 0;
    int headPosition = initialHeadPosition;
    int visited[100] = {0}; // Track visited requests
    int count = 0;

    while (count < n) {
        int closestIndex = findClosestTrack(RQ, n, headPosition, visited);
        if (closestIndex == -1) break;

        // Calculate movement for the closest track
        int distance = abs(RQ[closestIndex] - headPosition);
        totalHeadMovement += distance;
        headPosition = RQ[closestIndex];

        visited[closestIndex] = 1; // Mark this track as serviced
        count++;
    }

    return totalHeadMovement;
}

