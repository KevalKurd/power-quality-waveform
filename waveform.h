//
// Created by k3-mustafa on 30/04/2026.
//

#ifndef POWER_QUALITY_ANALYSER_WAVEFORM_H
#define POWER_QUALITY_ANALYSER_WAVEFORM_H
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

#endif
#endif //POWER_QUALITY_ANALYSER_WAVEFORM_H
