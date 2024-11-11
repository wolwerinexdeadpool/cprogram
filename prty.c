#include <stdio.h>

// Function prototypes
void inputProcesses(int n, int arrivalTimes[], int burstTimes[], int priorities[]);
void calculatePriorityWaitingTime(int n, int arrivalTimes[], int burstTimes[], int priorities[], int waitingTimes[]);
void calculateTurnaroundTime(int n, int burstTimes[], int waitingTimes[], int turnaroundTimes[]);
float calculateAverage(int n, int times[]);
void displayResults(int n, int arrivalTimes[], int burstTimes[], int waitingTimes[], int turnaroundTimes[]);

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int arrivalTimes[n], burstTimes[n], waitingTimes[n], turnaroundTimes[n], priorities[n];

    // Input the arrival, burst times, and priorities
    inputProcesses(n, arrivalTimes, burstTimes, priorities);

    // Calculate waiting time using Priority scheduling
    calculatePriorityWaitingTime(n, arrivalTimes, burstTimes, priorities, waitingTimes);

    // Calculate turnaround time for each process
    calculateTurnaroundTime(n, burstTimes, waitingTimes, turnaroundTimes);

    // Display process details and Gantt chart
    displayResults(n, arrivalTimes, burstTimes, waitingTimes, turnaroundTimes);

    // Calculate and display average waiting and turnaround times
    printf("Average Waiting Time: %.2f\n", calculateAverage(n, waitingTimes));
    printf("Average Turnaround Time: %.2f\n", calculateAverage(n, turnaroundTimes));

    return 0;
}

void inputProcesses(int n, int arrivalTimes[], int burstTimes[], int priorities[]) {
    printf("Enter Arrival Time, Burst Time, and Priority for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d - Arrival Time: ", i + 1);
        scanf("%d", &arrivalTimes[i]);
        printf("Process %d - Burst Time: ", i + 1);
        scanf("%d", &burstTimes[i]);
        printf("Process %d - Priority: ", i + 1);
        scanf("%d", &priorities[i]);
    }
}

void calculatePriorityWaitingTime(int n, int arrivalTimes[], int burstTimes[], int priorities[], int waitingTimes[]) {
    int completed = 0, elapsedTime = 0;
    int tempBurstTimes[n], tempPriorities[n], tempArrivalTimes[n];
    for (int i = 0; i < n; i++) {
        tempBurstTimes[i] = burstTimes[i];
        tempPriorities[i] = priorities[i];
        tempArrivalTimes[i] = arrivalTimes[i];
    }

    // Sorting based on priorities (higher priority first)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (tempPriorities[i] < tempPriorities[j]) {
                int temp = tempPriorities[i];
                tempPriorities[i] = tempPriorities[j];
                tempPriorities[j] = temp;

                temp = tempBurstTimes[i];
                tempBurstTimes[i] = tempBurstTimes[j];
                tempBurstTimes[j] = temp;

                temp = tempArrivalTimes[i];
                tempArrivalTimes[i] = tempArrivalTimes[j];
                tempArrivalTimes[j] = temp;
            }
        }
    }

    // Calculate waiting times for each process
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (tempBurstTimes[i] > 0) {
                waitingTimes[i] = elapsedTime - tempArrivalTimes[i];
                if (waitingTimes[i] < 0) waitingTimes[i] = 0;
                elapsedTime += tempBurstTimes[i];
                tempBurstTimes[i] = 0;
                completed++;
            }
        }
    }
}

void calculateTurnaroundTime(int n, int burstTimes[], int waitingTimes[], int turnaroundTimes[]) {
    for (int i = 0; i < n; i++) {
        turnaroundTimes[i] = waitingTimes[i] + burstTimes[i];
    }
}

float calculateAverage(int n, int times[]) {
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += times[i];
    }
    return (float)total / n;
}

void displayResults(int n, int arrivalTimes[], int burstTimes[], int waitingTimes[], int turnaroundTimes[]) {
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, arrivalTimes[i], burstTimes[i], waitingTimes[i], turnaroundTimes[i]);
    }

    // Display Gantt Chart
    printf("\nGantt Chart:\n");
    for (int i = 0; i < n; i++) {
        printf("|   P%d   ", i + 1);
    }
    printf("|\n");

    int elapsedTime = arrivalTimes[0];
    for (int i = 0; i < n; i++) {
        printf("%d\t", elapsedTime);
        elapsedTime += burstTimes[i];
    }
    printf("%d\n", elapsedTime);
}

