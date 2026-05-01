//
// Created by k3-mustafa on 30/04/2026.
//

#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "waveform.h"


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


WaveformSample *load_csv_file(const char *filename, int *count) {

    // Call function to count how many data rows are in the CSV file
    *count = count_rows(filename);

    // If file is empty or error occurred, return NULL
    if (*count <= 0) {
        return NULL;
    }

    // Open the file in read mode
    FILE *file = fopen(filename, "r");

    // Check if file opened successfully
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return NULL;
    }

    // Allocate memory dynamically for all rows
    // Each row becomes one WaveformSample struct
    WaveformSample *data = malloc(*count * sizeof(WaveformSample));

    // Check if malloc failed
    if (data == NULL) {
        printf("Error: Memory allocation failed.\n");

        // Always close file before exiting
        fclose(file);
        return NULL;
    }

    // Temporary buffer to store each line from file
    char line[256];

    // Skip the first line (header row in CSV)
    fgets(line, sizeof(line), file);

    // Loop through each row and store values into struct
    for (int i = 0; i < *count; i++) {

        // Read one line of CSV data and store values into struct fields
        fscanf(file, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
               &(data + i)->timestamp,          // time value
               &(data + i)->phase_A_voltage,    // phase A voltage
               &(data + i)->phase_B_voltage,    // phase B voltage
               &(data + i)->phase_C_voltage,    // phase C voltage
               &(data + i)->line_current,       // current
               &(data + i)->frequency,          // frequency
               &(data + i)->power_factor,       // power factor
               &(data + i)->thd_percent);       // harmonic distortion
    }

    // Close file after reading
    fclose(file);

    // Return pointer to dynamically allocated data array
    return data;
}
// Function to write analysis results to a text file
void write_results_file(const char *filename, WaveformSample *data, int count) {

    // Open file in write mode
    FILE *file = fopen(filename, "w");

    // Check if file opened correctly
    if (file == NULL) {
        printf("Error: Could not create results file.\n");
        return;
    }

    // --- Calculate RMS values once (efficient) ---
    double rms_A = calculate_rms(data, count, 'A');
    double rms_B = calculate_rms(data, count, 'B');
    double rms_C = calculate_rms(data, count, 'C');

    // --- Write report header ---
    fprintf(file, "Power Quality Waveform Analysis Report\n");
    fprintf(file, "======================================\n\n");

    // --- PHASE A RESULTS ---
    fprintf(file, "Phase A RMS: %.3f V\n", rms_A);
    fprintf(file, "Phase A Peak-to-Peak: %.3f V\n",
            calculate_peak_to_peak(data, count, 'A'));
    fprintf(file, "Phase A DC Offset: %.3f V\n",
            calculate_dc_offset(data, count, 'A'));
    fprintf(file, "Phase A Clipping Samples: %d\n",
            detect_clipping(data, count, 'A'));
    fprintf(file, "Phase A Tolerance: %s\n\n",
            check_tolerance(rms_A) ? "PASS" : "FAIL");

    // --- PHASE B RESULTS ---
    fprintf(file, "Phase B RMS: %.3f V\n", rms_B);
    fprintf(file, "Phase B Peak-to-Peak: %.3f V\n",
            calculate_peak_to_peak(data, count, 'B'));
    fprintf(file, "Phase B DC Offset: %.3f V\n",
            calculate_dc_offset(data, count, 'B'));
    fprintf(file, "Phase B Clipping Samples: %d\n",
            detect_clipping(data, count, 'B'));
    fprintf(file, "Phase B Tolerance: %s\n\n",
            check_tolerance(rms_B) ? "PASS" : "FAIL");

    // --- PHASE C RESULTS ---
    fprintf(file, "Phase C RMS: %.3f V\n", rms_C);
    fprintf(file, "Phase C Peak-to-Peak: %.3f V\n",
            calculate_peak_to_peak(data, count, 'C'));
    fprintf(file, "Phase C DC Offset: %.3f V\n",
            calculate_dc_offset(data, count, 'C'));
    fprintf(file, "Phase C Clipping Samples: %d\n",
            detect_clipping(data, count, 'C'));
    fprintf(file, "Phase C Tolerance: %s\n",
            check_tolerance(rms_C) ? "PASS" : "FAIL");

    // Close the file
    fclose(file);
}