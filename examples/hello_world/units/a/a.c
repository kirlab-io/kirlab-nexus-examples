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

#define PROCESS_SLOT (0)

/*Local process time*/
double t = 0.0;
double period = 10e-6;


/*Local buffer of shared values*/
double a_signal_0 = 1000.0;
double a_signal_1 = 2000.0;
double b_signal_0;
double b_signal_1;


/*Nexus callbacks*/
void write_data(void){
	nexus_pt->a.signal_0 = a_signal_0;
	nexus_pt->a.signal_1 = a_signal_1;
}

void read_data(void){
	b_signal_0 = nexus_pt->b.signal_0;
	b_signal_1 = nexus_pt->b.signal_1;
}

void simulation_finished(void){
    printf("\n\nSimulation finished.\n");
    exit(0);
}



int main(int argc, char *argv[]) {
    
	/*Nexus initialization*/
    int result = nexus_init(PROCESS_SLOT,
                            NEXUS_SHARED_ID); 
	
    if(result != 0) return result;
	
	nexus_set_read_callback(&read_data);
	nexus_set_write_callback(&write_data);
	nexus_set_finished_callback(&simulation_finished);
    
	
    printf("Read from other process: \nb.signal_0: %f\nb.signal_1:  %f\n", b_signal_0, b_signal_1);
    printf("Local time: %f\n", t);
    printf("\n\n");
    nexus_sync(period/2);
	
    while(1){
        t = t+period;
        nexus_sync(t);
        
        printf("Read from other process: \nb.signal_0: %f\nb.signal_1:  %f\n", b_signal_0, b_signal_1);
        printf("Local time: %f\n", t);
        printf("\n\n");
        
        a_signal_0 += 1.0;
        a_signal_1 += 1.0;
    }
    
    return 0;
}