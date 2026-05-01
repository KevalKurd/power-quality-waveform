//
// Created by k3-mustafa on 30/04/2026.
//

#include <stdio.h>
#include <stdlib.h>
#include "io.h"

int main(int argc, char *argv[]) {
    int count;                     // Will store number of samples in CSV
    WaveformSample *data;          // Pointer to dynamically allocated array

    // Check that the user provided a filename
    if (argc != 2) {
        printf("Usage: %s power_quality_log.csv\n", argv[0]);
        return 1;
    }

    // Load CSV data into memory using malloc
    data = load_csv_file(argv[1], &count);

    // Check if loading failed
    if (data == NULL) {
        printf("Program stopped because data could not be loaded.\n");
        return 1;
    }

    // Write analysis results to output file
    write_results_file("results.txt", data, count);

    // Free allocated memory to prevent memory leaks
    free(data);

    // Confirmation message to user
    printf("Analysis complete. Results written to results.txt\n");

    return 0;
}