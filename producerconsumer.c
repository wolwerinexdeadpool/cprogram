#include <stdio.h>
#include <stdlib.h>

int mutex = 1; // Ensures only one process can access the buffer at a time
int full = 0;  // Tracks filled slots in the buffer
int empty = 3; // Tracks empty slots in the buffer (buffer capacity is 3)
int item_count = 0; // Keeps count of the items produced

// Function prototypes
void producer();
void consumer();
int wait(int s);
int signal(int s);

int main() {
    int choice;
    printf("Menu:\n1. Producer\n2. Consumer\n3. Exit\n");

    while (1) {
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (mutex == 1 && empty != 0)
                    producer();
                else
                    printf("Buffer is full!!\n");
                break;

            case 2:
                if (mutex == 1 && full != 0)
                    consumer();
                else
                    printf("Buffer is empty!!\n");
                break;

            case 3:
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

// Decrease semaphore
int wait(int s) {
    return (--s);
}

// Increase semaphore
int signal(int s) {
    return (++s);
}

// Producer function to add items to the buffer
void producer() {
    mutex = wait(mutex);     // Lock access to the buffer
    full = signal(full);     // Increase full slots
    empty = wait(empty);     // Decrease empty slots
    item_count++;            // Produce an item
    printf("Producer produced item %d\n", item_count);
    mutex = signal(mutex);   // Release access to the buffer
}

// Consumer function to remove items from the buffer
void consumer() {
    mutex = wait(mutex);     // Lock access to the buffer
    full = wait(full);       // Decrease full slots
    empty = signal(empty);   // Increase empty slots
    printf("Consumer consumed item %d\n", item_count);
    item_count--;            // Consume an item
    mutex = signal(mutex);   // Release access to the buffer
}

