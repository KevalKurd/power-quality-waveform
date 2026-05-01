//
// Created by k3-mustafa on 30/04/2026.
//

#include <stdio.h>
#include <stdlib.h>
#include "io.h"

// Function to count how many data rows are in the CSV file
int count_rows(const char *filename) {

    // Open the file in read mode
    FILE *file = fopen(filename, "r");

    // Check if file opened successfully
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return -1; // return error value
    }

    int count = 0;          // stores number of data rows
    char line[256];         // buffer to store each line of the file

    // Read and ignore the first line (header row)
    fgets(line, sizeof(line), file);

    // Loop through the rest of the file line by line
    while (fgets(line, sizeof(line), file)) {
        count++;  // increase count for each data row
    }

    // Close the file to avoid memory/resource leaks
    fclose(file);

    // Return total number of rows found
    return count;
}