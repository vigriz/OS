#include <stdio.h>
#include <string.h>

int main() {
    FILE *fp;
    char filename[100], pattern[100], temp[100];
    
    printf("Enter filename: ");
    scanf("%s", filename);
    printf("Enter pattern: ");
    scanf("%s", pattern);
    
    // Open the file for reading
    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;  // Return a non-zero value to indicate an error
    }
    
    // Read each line from the file
    while (fgets(temp, sizeof(temp), fp) != NULL) {
        if (strstr(temp, pattern) != NULL) {
            printf("%s", temp);
        }
    }
    
    // Close the file

    
    fclose(fp);
    
    return 0;
}


Output:
Sample Input
Filename: example.txt
Pattern: search
Contents of example.txt:

This is a sample file.
It contains several lines.
Some of these lines contain the word search.
You can use this file to test the search functionality.
Have a good day!

Some of these lines contain the word search.
You can use this file to test the search functionality.

