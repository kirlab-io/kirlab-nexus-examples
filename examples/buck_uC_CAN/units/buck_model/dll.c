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

#include "nexus_com.h"
#include "nexus.h"



/*in and out from nexus*/
extern double * in;
extern double * out;

/*Exported values*/
const char * nexus_get_shared_id(void){
	return NEXUS_SHARED_ID;
}
const int nexus_process_slot = 0;
const int in_size = 4;
const int out_size = 2;

/*Exported functions*/
void nexus_write_shared_memory(void){
    nexus_pt->plant.v_in= in[0];
    nexus_pt->plant.i_in= in[1];
    nexus_pt->plant.v_out= in[2];
    nexus_pt->plant.i_out= in[3];
}
	
void nexus_read_shared_memory(void){
    out[0] = nexus_pt->controller.period;
    out[1] = nexus_pt->controller.duty_cycle;
}

void nexus_finished(void){
	//nothing to do, let the program run
}

void nexus_user_processing(void){
	//Do some extra processing...
}