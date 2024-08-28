//Compile the program using gcc -o
Run the compiled program with a number as a command-line argument: ./task_scheduler 5

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Global variable to store the value of n
int n;

// Thread functions
void *calculate_sum(void *arg) {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    printf("Sum of natural numbers up to %d: %d\n", n, sum);
    pthread_exit(NULL); // Terminate the thread
}

void *calculate_factorial(void *arg) {
    long long factorial = 1;
    for (int i = 1; i <= n; i++) {
        factorial *= i;
    }
    printf("Factorial of %d: %lld\n", n, factorial);
    pthread_exit(NULL); // Terminate the thread
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    n = atoi(argv[1]);
    if (n <= 0) {
        fprintf(stderr, "Please enter a positive integer.\n");
        exit(EXIT_FAILURE);
    }

    pthread_t thread1, thread2;

    // Create the first thread to calculate the sum
    if (pthread_create(&thread1, NULL, calculate_sum, NULL) != 0) {
        perror("Failed to create thread 1");
        exit(EXIT_FAILURE);
    }

    // Create the second thread to calculate the factorial
    if (pthread_create(&thread2, NULL, calculate_factorial, NULL) != 0) {
        perror("Failed to create thread 2");
        exit(EXIT_FAILURE);
    }

    // Wait for both threads to complete
    if (pthread_join(thread1, NULL) != 0) {
        perror("Failed to join thread 1");
        exit(EXIT_FAILURE);
    }

    if (pthread_join(thread2, NULL) != 0) {
        perror("Failed to join thread 2");
        exit(EXIT_FAILURE);
    }

    printf("Both threads have completed execution.\n");

    return 0;
}

Output:
gcc -o task_scheduler task_scheduler.c -pthread
./task_scheduler 5
Sum of natural numbers up to 5: 15
Factorial of 5: 120
Both threads have completed execution.
