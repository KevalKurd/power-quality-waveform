#include <math.h>
#include "waveform.h"

// This function returns the voltage for the selected phase (A, B or C)
double get_phase_voltage(WaveformSample *sample, char phase) {
    if (phase == 'A')
        return sample->phase_A_voltage;
    else if (phase == 'B')
        return sample->phase_B_voltage;
    else
        return sample->phase_C_voltage;
}

// This function calculates RMS voltage for a given phase
double calculate_rms(WaveformSample *data, int count, char phase) {
    double sum = 0.0;     // stores sum of squared values
    double value;         // current voltage value

    // loop through all samples
    for (int i = 0; i < count; i++) {

        // get voltage using pointer arithmetic
        value = get_phase_voltage(data + i, phase);

        // square the value and add to sum
        sum += value * value;
    }

    // return RMS = sqrt(mean of squares)
    return sqrt(sum / count);
}

// This function calculates peak-to-peak voltage
double calculate_peak_to_peak(WaveformSample *data, int count, char phase) {

    // start by assuming first value is both min and max
    double max = get_phase_voltage(data, phase);
    double min = get_phase_voltage(data, phase);
    double value;

    // loop through remaining samples
    for (int i = 1; i < count; i++) {

        value = get_phase_voltage(data + i, phase);

        // update max if larger value found
        if (value > max)
            max = value;

        // update min if smaller value found
        if (value < min)
            min = value;
    }

    // peak-to-peak = max - min
    return max - min;
}
// Calculate DC offset (average voltage)
double calculate_dc_offset(WaveformSample *data, int count, char phase) {
    double sum = 0.0;
    double value;

    for (int i = 0; i < count; i++) {
        value = get_phase_voltage(data + i, phase);
        sum += value;
    }

    // Mean value
    return sum / count;
}

// Count how many samples exceed clipping limit
int detect_clipping(WaveformSample *data, int count, char phase) {
    int clipping_count = 0;
    double value;

    for (int i = 0; i < count; i++) {

        value = get_phase_voltage(data + i, phase);

        // Check both positive and negative peaks
        if (fabs(value) >= 324.9) {
            clipping_count++;
        }
    }

    return clipping_count;
}