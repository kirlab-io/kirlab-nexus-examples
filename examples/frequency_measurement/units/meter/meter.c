/*
=========================================================================
* Copyright (C) 2023 Kirlab
* All rights reserved.
*
* This file is part of KirLab Nexus.
*
* This file is distributed under the terms of KirLab Nexus license.
* Please see the EULA.txt file for the full license text.
=========================================================================
*/
#include "nexus.h"
#include <stdio.h>
#include <math.h>

#define PROCESS_SLOT (1)

double t;
double period = 10e-6;

double input_signal;

double measured_frequency;
double measured_amplitude;

#ifdef __cplusplus
extern "C" {
#endif
void nexus_write_shared_memory(void){
    nexus_pt->measured_frequency = measured_frequency;
    nexus_pt->measured_amplitude = measured_amplitude;
}

void nexus_read_shared_memory(void){
    input_signal = nexus_pt->generated_signal;
}
#ifdef __cplusplus
}
#endif



double previous_value = 0;
double last_time_since_zero_crossing = 0;
double time_since_zero_crossing = 0;
double peak_value = 0;

void meter(double signal, double *frequency, double *amplitude, double step) {
    time_since_zero_crossing += step;

    // Check for zero crossing (from positive to negative)
    if (previous_value > 0 && signal <= 0) {
        *frequency = 1.0 / time_since_zero_crossing;
        last_time_since_zero_crossing = time_since_zero_crossing;
        time_since_zero_crossing = 0;
    }

    // Check for peak value
    if (fabs(signal) > fabs(peak_value)) {
        peak_value = signal;
    }

    // If a complete cycle is detected, update amplitude
    if (time_since_zero_crossing == 0) {
        *amplitude = fabs(peak_value);
        peak_value = 0;
    }

    previous_value = signal;
}


int main(int argc, char *argv[]) {
    
    int result = nexus_init(PROCESS_SLOT,
                            nexus_shared_id);     
    if(result != 0) return result;
    
    printf("Meter\n");
    while(1){
        
        t = t+period;
        nexus_sync(t);
        
        meter(input_signal,&measured_frequency, &measured_amplitude, period);
        printf("\r(t = %f) %fHz %fVpp raw=%fV", 
            t, 
            measured_frequency,
            measured_amplitude,
            input_signal);
        
    }
    
    return 0;
}
