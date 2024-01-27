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
#include <nexus.h>
#include <stdlib.h>
#include <stdio.h>
#include "application.h"

#define PROCESS_SLOT (1)

/*Local process time*/
double t;
double period = 10e-6;


/*Nexus callbacks*/
void write_data(void){
	nexus_pt->controller_signals.pwm_duty_cycle = pwm_duty_cycle;
}

void read_data(void){
	output_voltage = nexus_pt->power_signals.output_voltage;
}

void simulation_finished(void){
    printf("\n\nSimulation finished.\n");
    exit(0);
}


int main(int argc, char *argv[]) {
    
	int result = nexus_init(PROCESS_SLOT,
                            NEXUS_SHARED_ID); 

	if(result != 0) 
		return result;
	
	nexus_set_read_callback(&read_data);
	nexus_set_write_callback(&write_data);
	nexus_set_finished_callback(&simulation_finished);
	

	application_init();
	while(1){
		t = t+period;
		application_task();
		nexus_sync(t);
	}
	
	return 0;
}
