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

#include "nexus_uC.h" 
#include "nexus.h"

/*in and out from nexus*/
extern double * in;
extern double * out;

/*Import simulation time*/
extern double simulation_t;
extern double step_dt;

/*Exported values*/
const int in_size = 2;
const int out_size = 1;

/*Local data*/
void* pwm0_aux;

/*Exported functions*/
void init(void){
    (void)nexus_init(0, NEXUS_SHARED_ID);
    pwm0_aux = nexus_uC_pwm_aux_create();
}

void write_data(void){
    nexus_pt->power_signals.output_voltage = in[0];
    nexus_pt->power_signals.output_current = in[1];
}

void read_data(void){
    nexus_uC_pwm_aux_load(pwm0_aux, nexus_pt->controller_signals.pwm_link);
}
	
void finished(void){
    //Do something at the end of the simulation...
}

void processing(void){
	nexus_uC_pwm_aux_update(pwm0_aux, simulation_t, step_dt);
    out[0] = nexus_uC_pwm_aux_get_output(pwm0_aux);
}