//
// Created by k3-mustafa on 30/04/2026.
//

#include <math.h> //For sqrt() function
#include "waveform.h" //Includes the waveform struct

//Function to calculate RMS Voltage for a selected phase (A, B or C)
double calculate_rms(WaveformSample *data, int count, char phase) {
    double sum = 0.0; //Stores sum of squared voltage values
    double value; //Temporary variable to hold each sample value

    //Loop through all samples in the dataset
    for (int i = 0; i < count; i++) {

        //Select which phase voltage to use based on input character
        if (phase == 'A')
            value = (data + i)->phase_A_voltage;
        else if (phase == 'B')
            value = (data + i)->phase_B_voltage;
        else
            value = (data + i)->phase_C_voltage;

        sum += value * value;
    }

    return sqrt(sum / count);
}