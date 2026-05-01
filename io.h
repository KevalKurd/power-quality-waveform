//
// Created by k3-mustafa on 30/04/2026.
//

#ifndef IO_H
#define IO_H

#include "waveform.h"

// Count number of data rows in CSV
int count_rows(const char *filename);

// Load CSV into dynamically allocated array
WaveformSample *load_csv_file(const char *filename, int *count);

// Write analysis results to file
void write_results_file(const char *filename, WaveformSample *data, int count);

#endif