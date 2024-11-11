#include<stdio.h>
#include <stdbool.h>  // To use the 'bool' type

int max[10][10];       // max requirement
int allocation[10][10]; // already allocated to process
int need[10][10];       // what it requires max req - allocation
int avail[10];          // the available resources or work
int np, nr;             // no of processes, no of resources

void readmatrix(int matrix[10][10]) { // generalized function to read matrix
    int i, j;
    for (i = 0; i < np; i++) {
        for (j = 0; j < nr; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}

void display_matrix(int matrix[10][10]) { // generalized function to print the given matrix
    int i, j;
    for (i = 0; i < np; i++) {
        printf("\n P%d", i);
        for (j = 0; j < nr; j++) {
            printf("  %d", matrix[i][j]);
        }
    }
}

void calculate_need() { // using the simple formula need = max - alloc iteratively to get need matrix
    int i, j;
    for (i = 0; i < np; i++) {
        for (j = 0; j < nr; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

void banker() {
    int i, j;
    int k = 0;  // first index of safe sequence array
   bool canallocate = false;
    int finish[10]; // to check if all process completed to determine whether deadlock has occurred or not.
    int safe_seq[10];
    bool all_process_completed = true;

    // initialize this processes_completed or finish array to 0 because no process is complete at the beginning
    for (i = 0; i < np; i++) {
        finish[i] = 0;
    }

    // loop until all processes are finished or deadlock is detected
    while (1) {
        int progress = 0; // To track whether any process has made progress in this cycle

        for (i = 0; i < np; i++) { // i here is process
                if (finish[i] == 0) { // if not complete
                           for (j = 0; j < nr; j++)
                           {
                                    if (need[i][j] <= avail[j]) 
                                    {
                                        canallocate = true; 
                                     }
                                   else
                                   {
                                          canallocate = false;
                                          break;
                                   }
                            }
                      if (canallocate) { // if need is less than or equal to available
                         finish[i] = 1; // finish the process
                         safe_seq[k] = i; // safe sequence
                          k++;
                          
                    // Add the allocation of the finished process to available resources
                    for (j = 0; j < nr; j++) {
                        avail[j] += allocation[i][j];
                    }
                    progress = 1; // Process was able to complete
                }
            }
        }

        // If no process was able to complete in this cycle, break and check for deadlock
        if (!progress) {
            break;
        }
    }

    // Check if all processes have finished or if deadlock occurred
    for (i = 0; i < np; i++) {
        if (finish[i] == 0) {
            printf("\nThe system is in deadlock\n");
            all_process_completed = false;
            break;
        }
    }

    if (all_process_completed) {
        printf("\nThe system is in a safe state! \nSafe sequence is: ");
        for (i = 0; i < np; i++) {
            printf("P%d ", safe_seq[i]);
        }
    }
}

int main() {
    int j;
    printf("\nEnter number of processes: ");
    scanf("%d", &np);
    printf("\nEnter number of resources: ");
    scanf("%d", &nr);

    printf("\nEnter initial allocation matrix: \n");
    readmatrix(allocation);

    printf("\nEnter Max requirement matrix:  \n");
    readmatrix(max);

    printf("\nEnter available resources: ");
    for (j = 0; j < nr; j++) {
        scanf("%d", &avail[j]);
    }

    printf("\n****** Entered Data is ******\n\n");

    printf("\nInitial allocation: \n");
    display_matrix(allocation);

    printf("\n\nMaximum Requirement: \n");
    display_matrix(max);

    printf("\nAvailable Resources: ");
    for (j = 0; j < nr; j++) {
        printf(" %d", avail[j]);
    }

    // Calculate and display need
    calculate_need();
    printf("\n\nNeed matrix: \n");
    display_matrix(need);

    banker();

    return 0;
}

