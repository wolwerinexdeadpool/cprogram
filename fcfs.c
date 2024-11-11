#include <stdio.h>
#include <stdlib.h>

// Function Prototypes
void inputRequests(int RQ[], int *n);
int calculateTotalHeadMovement(int RQ[], int n, int initialHeadPosition);

int main() {
    int RQ[100], n, initialHeadPosition, totalHeadMovement;

    // Input the number of requests and the sequence of requests
    inputRequests(RQ, &n);

    // Input the initial position of the disk head
    printf("Enter initial head position: ");
    scanf("%d", &initialHeadPosition);

    // Calculate the total head movement using FCFS disk scheduling algorithm
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

// Function to calculate the total head movement using FCFS scheduling
int calculateTotalHeadMovement(int RQ[], int n, int initialHeadPosition) {
    int totalHeadMovement = 0;

    for (int i = 0; i < n; i++) {
        // Calculate absolute distance and add to total movement
        totalHeadMovement += abs(RQ[i] - initialHeadPosition);
        
        // Move the head to the current request's position
        initialHeadPosition = RQ[i];
    }

    return totalHeadMovement;
}

