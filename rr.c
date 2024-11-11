#include <stdio.h>

// Function prototypes
void inputProcesses(int n, int arrivalTimes[], int burstTimes[], int priorities[], int timeQuantum);
void calculateRRWaitingTime(int n, int arrivalTimes[], int burstTimes[], int waitingTimes[], int timeQuantum);
void calculateTurnaroundTime(int n, int burstTimes[], int waitingTimes[], int turnaroundTimes[]);
float calculateAverage(int n, int times[]);
void displayResults(int n, int arrivalTimes[], int burstTimes[], int waitingTimes[], int turnaroundTimes[]);

int main() {
    int n, timeQuantum;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter time quantum: ");
    scanf("%d", &timeQuantum);

    int arrivalTimes[n], burstTimes[n], waitingTimes[n], turnaroundTimes[n], priorities[n];

    // Input the arrival and burst times
    inputProcesses(n, arrivalTimes, burstTimes, priorities, timeQuantum);

    // Calculate waiting time using Round Robin scheduling
    calculateRRWaitingTime(n, arrivalTimes, burstTimes, waitingTimes, timeQuantum);

    // Calculate turnaround time for each process
    calculateTurnaroundTime(n, burstTimes, waitingTimes, turnaroundTimes);

    // Display process details and Gantt chart
    displayResults(n, arrivalTimes, burstTimes, waitingTimes, turnaroundTimes);

    // Calculate and display average waiting and turnaround times
    printf("Average Waiting Time: %.2f\n", calculateAverage(n, waitingTimes));
    printf("Average Turnaround Time: %.2f\n", calculateAverage(n, turnaroundTimes));

    return 0;
}

void inputProcesses(int n, int arrivalTimes[], int burstTimes[], int priorities[], int timeQuantum) {
    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d - Arrival Time: ", i + 1);
        scanf("%d", &arrivalTimes[i]);
        printf("Process %d - Burst Time: ", i + 1);
        scanf("%d", &burstTimes[i]);
    }
}

void calculateRRWaitingTime(int n, int arrivalTimes[], int burstTimes[], int waitingTimes[], int timeQuantum) {
    int remainingBurstTimes[n], elapsedTime = 0, completed = 0;
    int currentProcess;

    // Initialize remaining burst times
    for (int i = 0; i < n; i++) {
        remainingBurstTimes[i] = burstTimes[i];
    }

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (remainingBurstTimes[i] > 0) {
                if (remainingBurstTimes[i] <= timeQuantum) {
                    elapsedTime += remainingBurstTimes[i];
                    remainingBurstTimes[i] = 0;
                    waitingTimes[i] = elapsedTime - arrivalTimes[i] - burstTimes[i];
                    completed++;
                } else {
                    elapsedTime += timeQuantum;
                    remainingBurstTimes[i] -= timeQuantum;
                }
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

