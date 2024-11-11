#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

void createFile(char *filename);
void readFile(char *filename);
void writeFile(char *filename);

int main(int argc, char *argv[]) {
    pid_t pid;
    int status;

    // Fork system call to create child process
    pid = fork();
    if (pid == -1) {
        // Error in creating process
        printf("Process creation unsuccessful\n");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        printf("Child process\n");
        printf("Child Process ID: %d\n", getpid());
        printf("Parent Process ID: %d\n", getppid());
        createFile(argv[1]);  // Create a file
        readFile(argv[1]);    // Read the file
        writeFile(argv[1]);   // Write to the file
        exit(0);  // Exit the child process
    } else {
        // Parent process
        printf("Parent process\n");
        printf("Parent Process ID: %d\n", getpid());
        printf("Parent's Parent Process ID: %d\n", getppid());
        
        // Wait for the child to finish execution
        waitpid(pid, &status, 0);

        // Check if child exited normally
        if (WIFEXITED(status)) {
            printf("Child process exited with status %d\n", WEXITSTATUS(status));
        } else {
            printf("Child process did not exit normally\n");
        }
        exit(0);  // Exit the parent process
    }
    return 0;
}

// Function to create a file and write content to it
void createFile(char *filename) {
    int fd;
    char buf[100];

    // Open the file for writing, create if doesn't exist, and truncate if exists
    fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("File creation problem");
        exit(-1);
    }
    printf("File created successfully\n");

    // Read from stdin and write to file until Ctrl+D (EOF) is entered
    printf("Press Ctrl+D to end input:\n");
    while (fgets(buf, sizeof(buf), stdin) != NULL) {
        write(fd, buf, strlen(buf));
    }

    // Close the file after writing
    close(fd);
    printf("File writing completed\n");
}

// Function to read content from a file
void readFile(char *filename) {
    int fd;
    char buf[100];

    // Open the file for reading
    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        printf("File does not exist: %s\n", filename);
        exit(-1);
    }

    // Read and print content of the file until EOF
    printf("Contents of the file %s:\n", filename);
    while (read(fd, buf, sizeof(buf)) > 0) {
        printf("%s", buf);
    }

    // Close the file after reading
    close(fd);
}

// Function to append content to a file
void writeFile(char *filename) {
    int fd;
    char buf[100];

    // Open the file for appending (create if doesn't exist)
    fd = open(filename, O_APPEND | O_WRONLY | O_CREAT, 0644);
    if (fd < 0) {
        perror("Error opening file");
        exit(-1);
    }
    printf("File opened for appending\n");
}
    // Read from stdin and append to file until Ctrl+D

