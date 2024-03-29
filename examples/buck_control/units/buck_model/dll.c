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



/*in and out from nexus*/
extern double * in;
extern double * out;

/*Exported values*/
const int in_size = 4;
const int out_size = 2;

/*Callbacks*/
void init(void){
    (void)nexus_init(0, NEXUS_SHARED_ID);
}

void write_data(void){
    nexus_pt->plant.v_in= in[0];
    nexus_pt->plant.i_in= in[1];
    nexus_pt->plant.v_out= in[2];
    nexus_pt->plant.i_out= in[3];
}
	
void read_data(void){
    out[0] = nexus_pt->controller.period;
    out[1] = nexus_pt->controller.duty_cycle;
}

void finished(void){
	//nothing to do, let the program run
}

void processing(void){
	//Do some extra processing...
}