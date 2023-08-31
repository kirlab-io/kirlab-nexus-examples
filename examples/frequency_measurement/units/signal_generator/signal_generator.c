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
#include <stdlib.h>
#include <math.h>

#define PROCESS_SLOT (0)

double t;
double period = 10e-6;

double generated_signal = 0;
double requested_frequency = 1e3;
double requested_amplitude = 320.0;

#ifdef __cplusplus
extern "C" {
#endif
void nexus_write_shared_memory(void){
	nexus_pt->generated_signal = generated_signal;
}

void nexus_read_shared_memory(){
    requested_amplitude = nexus_pt->requested_amplitude;
    requested_frequency = nexus_pt->requested_frequency;
}

void nexus_finished(void){
    printf("\n\nSimulation finished, press Enter to exit...");
    getchar();
    exit(0);
}
#ifdef __cplusplus
}
#endif


double sine_wave(double time, double frequency, double amplitude){
    double omega = 2 * M_PI * frequency;
    return amplitude * sin(omega * time); 
}

int main(int argc, char *argv[]) {
    
    int result = nexus_init(PROCESS_SLOT,
                            NEXUS_SHARED_ID); 
    if(result != 0) return result;
 
    printf("Generator\n");
    while(1){
        t = t+period;
        nexus_sync(t);
        
        generated_signal = sine_wave(t, requested_frequency, requested_amplitude);
        printf("\r(t = %f) %fHz %fVpp raw=%fV", 
                t,
                requested_frequency, 
                requested_amplitude,
                generated_signal);
    }
    
    return 0;
}