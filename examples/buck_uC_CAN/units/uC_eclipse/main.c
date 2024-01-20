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
#include <nexus_comm.h>
#include <nexus_uC.h>
#include <nexus.h>
#include <stdlib.h>
#include <stdio.h>
#include "application.h"
#include "hardware.h"

/*Local process time*/
double dt = 1e-6;
double unit_t = 0.0;

/*Slot*/
int nexus_uC_slot = 1;


/*Nexus callbacks*/
void write_data(void){
	nexus_pt->controller.period = period;
	nexus_pt->controller.duty_cycle = duty_cycle;
}

void read_data(void){
	v_in = nexus_pt->plant.v_in;
	i_in = nexus_pt->plant.i_in;
	v_out = nexus_pt->plant.v_out;
	i_out = nexus_pt->plant.i_out;
}

void simulation_finished(void){
    printf("\n\nSimulation finished.\n");
    exit(0);
}



int main(int argc, char *argv[]) {

	/*Initialize nexus*/
	int result = nexus_init(nexus_uC_slot,
							NEXUS_SHARED_ID);
	if(result != 0)
		return result;
	nexus_set_read_callback(&read_data);
	nexus_set_write_callback(&write_data);
	nexus_set_finished_callback(&simulation_finished);
	

	/*Initialize the uC*/
	nexus_uC_init();
	create_hardware();

	/*Finally initialize the user application*/
	application_init();

	/*Loop forever*/
	while(1){

		/*Update the uC*/
		unit_t += dt;
		nexus_uC_step(unit_t);

		/*Call the application background loop*/
		application_background_loop();

		/*Sync*/
		nexus_sync(unit_t);
	}
	
	return 0;
}
