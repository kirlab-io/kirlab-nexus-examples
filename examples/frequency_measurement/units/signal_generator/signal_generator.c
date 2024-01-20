/*
=========================================================================
* Copyright (C) 2024 Kirlab
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

/*Local process time*/
double t;
double period = 10e-6;


/*Local buffer of shared values*/
double generated_signal = 0;
double requested_frequency = 1e3;
double requested_amplitude = 320.0;


/*Nexus callbacks*/
void write_data(void){
	nexus_pt->generated_signal = generated_signal;
}

void read_data(){
    requested_amplitude = nexus_pt->requested_amplitude;
    requested_frequency = nexus_pt->requested_frequency;
}

void simulation_finished(void){
    printf("\n\nSimulation finished.\n");
    exit(0);
}


/*Local application*/
double sine_wave(double time, double frequency, double amplitude){
    double omega = 2 * M_PI * frequency;
    return amplitude * sin(omega * time); 
}

int main(int argc, char *argv[]) {
    
	/*Nexus initialization*/
    int result = nexus_init(PROCESS_SLOT,
                            NEXUS_SHARED_ID); 
    if(result != 0) return result;
	
	nexus_set_read_callback(&read_data);
	nexus_set_write_callback(&write_data);
	nexus_set_finished_callback(&simulation_finished);
	
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