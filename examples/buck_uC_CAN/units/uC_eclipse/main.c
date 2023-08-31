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
#include <nexus_com.h>
#include <nexus_uC.h>
#include <nexus.h>
#include <stdlib.h>
#include <stdio.h>
#include "application.h"
#include "hardware.h"

//Nexus vars
double dt = 1e-6;
double unit_t = 0.0;
int nexus_uC_slot = 1;


#ifdef __cplusplus
extern "C" {
#endif
void nexus_write_shared_memory(void){
	nexus_pt->controller.period = period;
	nexus_pt->controller.duty_cycle = duty_cycle;
}

void nexus_read_shared_memory(int argc, char *argv[]){
	v_in = nexus_pt->plant.v_in;
	i_in = nexus_pt->plant.i_in;
	v_out = nexus_pt->plant.v_out;
	i_out = nexus_pt->plant.i_out;
}

void nexus_finished(void){
    printf("Simulation finished");
    exit(0);
}
#ifdef __cplusplus
}
#endif




int main(int argc, char *argv[]) {

	int result = nexus_init(nexus_uC_slot,
							NEXUS_SHARED_ID);
	if(result != 0)
		return result;
	
	nexus_uC_init();
	create_hardware();
	application_init();

	while(1){
		unit_t += dt;
		nexus_uC_step(unit_t);
		application_background_loop();
		nexus_sync(unit_t);
	}
	
	return 0;
}
