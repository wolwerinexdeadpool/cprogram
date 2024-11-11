#include <stdio.h>

// Function prototypes
void inputProcesses(int n, int arrivalTimes[], int burstTimes[]);
void sortProcessesByBurstTime(int n, int burstTimes[], int arrivalTimes[], int processID[]);
void calculateSJFWaitingTime(int n, int burstTimes[], int waitingTimes[]);
void calculateTurnaroundTime(int n, int burstTimes[], int waitingTimes[], int turnaroundTimes[]);
float calculateAverage(int n, int times[]);
void displayResults(int n, int arrivalTimes[], int burstTimes[], int waitingTimes[], int turnaroundTimes[], int processID[]);

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int arrivalTimes[n], burstTimes[n], waitingTimes[n], turnaroundTimes[n], processID[n];

    // Input arrival and burst times
    inputProcesses(n, arrivalTimes, burstTimes);

    // Assign process IDs
    for (int i = 0; i < n; i++) processID[i] = i + 1;

    // Sort processes by burst time for SJF scheduling
    sortProcessesByBurstTime(n, burstTimes, arrivalTimes, processID);

    // Calculate waiting time
    calculateSJFWaitingTime(n, burstTimes, waitingTimes);

    // Calculate turnaround time
    calculateTurnaroundTime(n, burstTimes, waitingTimes, turnaroundTimes);

    // Display results
    displayResults(n, arrivalTimes, burstTimes, waitingTimes, turnaroundTimes, processID);

    // Calculate and display averages
    printf("Average Waiting Time: %.2f\n", calculateAverage(n, waitingTimes));
    printf("Average Turnaround Time: %.2f\n", calculateAverage(n, turnaroundTimes));

    return 0;
}

void inputProcesses(int n, int arrivalTimes[], int burstTimes[]) {
    printf("Enter Arrival Time and Burst Time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d - Arrival Time: ", i + 1);
        scanf("%d", &arrivalTimes[i]);
        printf("Process %d - Burst Time: ", i + 1);
        scanf("%d", &burstTimes[i]);
    }
}

// Sort processes by burst time (non-preemptive SJF)
void sortProcessesByBurstTime(int n, int burstTimes[], int arrivalTimes[], int processID[]) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (burstTimes[i] > burstTimes[j]) {
                // Swap burst time
                int temp = burstTimes[i];
                burstTimes[i] = burstTimes[j];
                burstTimes[j] = temp;

                // Swap arrival time
                temp = arrivalTimes[i];
                arrivalTimes[i] = arrivalTimes[j];
                arrivalTimes[j] = temp;

                // Swap process ID
                temp = processID[i];
                processID[i] = processID[j];
                processID[j] = temp;
            }
        }
    }
}

void calculateSJFWaitingTime(int n, int burstTimes[], int waitingTimes[]) {
    waitingTimes[0] = 0; // First process has no waiting time

    for (int i = 1; i < n; i++) {
        waitingTimes[i] = waitingTimes[i - 1] + burstTimes[i - 1];
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

void displayResults(int n, int arrivalTimes[], int burstTimes[], int waitingTimes[], int turnaroundTimes[], int processID[]) {
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processID[i], arrivalTimes[i], burstTimes[i], waitingTimes[i], turnaroundTimes[i]);
    }

    // Display Gantt Chart
    printf("\nGantt Chart:\n");
    for (int i = 0; i < n; i++) {
        printf("|   P%d   ", processID[i]);
    }
    printf("|\n");

    int elapsedTime = 0;
    for (int i = 0; i < n; i++) {
        printf("%d\t", elapsedTime);
        elapsedTime += burstTimes[i];
    }
    printf("%d\n", elapsedTime);
}

