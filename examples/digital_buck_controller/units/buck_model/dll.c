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
const int in_size = 2;
const int out_size = 1;

/*Exported functions*/
void init(void){
    (void)nexus_init(0, NEXUS_SHARED_ID);
}

void write_data(void){
    nexus_pt->power_signals.output_voltage = in[0];
    nexus_pt->power_signals.output_current = in[1];
}

void read_data(void){
    out[0] = nexus_pt->controller_signals.pwm_duty_cycle;
}
	
void finished(void){
    //Do something at the end of the simulation...
}

void processing(void){
	//Do some extra processing...
}