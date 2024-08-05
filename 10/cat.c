//compile with gcc -o my_cat my_cat.c
//Run the compiled program with a filename as an argument: ./my_cat somefile.txt

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int fd;
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead;

    // Open the file
    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Read and write the file contents
    while ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0) {
        if (write(STDOUT_FILENO, buffer, bytesRead) < 0) {
            perror("Error writing to stdout");
            close(fd);
            exit(EXIT_FAILURE);
        }
    }

    // Check for read error
    if (bytesRead < 0) {
        perror("Error reading file");
    }

    // Close the file
    if (close(fd) < 0) {
        perror("Error closing file");
        exit(EXIT_FAILURE);
    }

    return 0;
}
