#include <stdio.h>
#define NUM_PHILOSOPHERS 4  // Number of philosophers and forks

int philosophersFinishedEating = 0;
int forkStatus[NUM_PHILOSOPHERS] = {0}; // Array to track fork availability (0 = available, 1 = taken)

// Function to simulate the dining behavior of a philosopher
void attemptToEat(int philosopherID) {
    // If all philosophers have finished eating, exit
    if (philosophersFinishedEating >= NUM_PHILOSOPHERS) {
        return;
    }

    // Try to pick up the left fork
    if (forkStatus[philosopherID] == 0) {  // Left fork is available
        forkStatus[philosopherID] = 1;  // Mark the left fork as taken
        printf("Philosopher %d picked up left fork %d\n", philosopherID + 1, philosopherID + 1);

        // Try to pick up the right fork
        int rightForkID = (philosopherID + 1) % NUM_PHILOSOPHERS; //bwcuase for 4th philospher 4+1 would become 5 which isnt a valid fork no and so we make it pick the first one so 5%4 = 1// simply make last philosopher pick in reverse
        if (forkStatus[rightForkID] == 0) {  // Right fork is available
            forkStatus[rightForkID] = 1;  // Mark the right fork as taken
            printf("Philosopher %d picked up right fork %d\n", philosopherID + 1, rightForkID + 1);

            // Philosopher can now eat
            printf("Philosopher %d is eating.\n", philosopherID + 1);
            
            // After eating, put down both forks
            forkStatus[philosopherID] = 0;  // Release left fork
            printf("Philospher %d puts down fork %d\n",philosopherID+1,philosopherID+1);
            forkStatus[rightForkID] = 0;    // Release right fork
            printf("Philosopher %d put down fork %d \n", philosopherID + 1, rightForkID + 1);

            philosophersFinishedEating++;
            printf("Philosopher %d has finished eating.\n\n", philosopherID + 1);
        } else {
            // Right fork is not available, so put down the left fork
            forkStatus[philosopherID] = 0;
            printf("Philosopher %d couldn't pick up right fork %d and put down left fork %d\n", philosopherID + 1, rightForkID + 1, philosopherID + 1);
        }
    } else {
        printf("Philosopher %d is waiting for left fork %d\n", philosopherID + 1, philosopherID + 1);
    }
}

int main() {
    // Keep running until all philosophers have finished eating
    while (philosophersFinishedEating < NUM_PHILOSOPHERS) {
        for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
            attemptToEat(i);
        }
    }

    printf("All philosophers have finished eating.\n");
    return 0;
}

