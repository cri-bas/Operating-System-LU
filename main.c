#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Function to be executed by thread to count how many lines exist in a file
extern void *count_lines(void *arg);

int main() {
    // Open the file data.txt and obtain the file handler fh
    FILE *fh = fopen("data.txt", "r");

    if (fh == NULL) {
        perror("Error opening file");
        exit(1);
    }

    // Declare my_thread thread
    pthread_t my_thread;

    // Create a thread my_thread using pthread_create; then pass fh to my_thread
    if (pthread_create(&my_thread, NULL, count_lines, fh) != 0) {
        perror("Error creating thread");
        exit(1);
    }

    // Create a variable to store the number of lines (pointer)
    int *num_lines;

    // Wait until my_thread terminates, using pthread_join
    if (pthread_join(my_thread, (void**)&num_lines) != 0) {
        perror("Error joining thread");
        exit(1);
    }

    // Close the file
    fclose(fh);

    // Print out how many lines exist in data.txt
    printf("Number of lines in data.txt: %d\n", *num_lines);

    // Free the allocated memory for num_lines
    free(num_lines);

    return 0;
}
