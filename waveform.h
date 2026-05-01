//
// Created by k3-mustafa on 30/04/2026.
//

#ifndef WAVEFORM_H
#define WAVEFORM_H

typedef struct {
    double timestamp;
    double phase_A_voltage;
    double phase_B_voltage;
    double phase_C_voltage;
    double line_current;
    double frequency;
    double power_factor;
    double thd_percent;

} WaveformSample;

// Function Version1.0
double calculate_rms(WaveformSample *data, int count, char phase);
double calculate_peak_to_peak(WaveformSample *data, int count, char phase);
double calculate_dc_offset(WaveformSample *data, int count, char phase);
int detect_clipping(WaveformSample *data, int count, char phase);

#endif