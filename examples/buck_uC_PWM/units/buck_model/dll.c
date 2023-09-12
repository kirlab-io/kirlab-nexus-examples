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

#include "nexus_uC.h"
#include "nexus_uC_pwm_dst.h"
#include "nexus.h"

/*time*/
extern double simulation_t;
extern double step_dt;

/*in and out from nexus*/
extern double * in;
extern double * out;

/*Exported values*/
const char * get_shared_id(void){
	return NEXUS_SHARED_ID;
}
const int unit_slot = 0;
const int in_size = 4;
const int out_size = 1;

/*local data*/
void * pwms[1];

void * nexus_uC_pwm_dst_create(void);

/*Callbacks*/
void init(void){
	for(int i=0; i<sizeof(pwms)/sizeof(pwms[0]); i++){
        pwms[i] = nexus_uC_pwm_dst_create();
        nexus_uC_pwm_dst_set_shared_object(pwms[i], (void *)&nexus_pt->pwm_links[i]);
        nexus_uC_pwm_dst_set_all_pwms(pwms[i], pwms, sizeof(pwms)/sizeof(pwms[0]));
    }
}

void write_data(void){
    nexus_pt->plant.v_in= in[0];
    nexus_pt->plant.i_in= in[1];
    nexus_pt->plant.v_out= in[2];
    nexus_pt->plant.i_out= in[3];
}
	
void read_data(void){
	for(int i=0; i<sizeof(pwms)/sizeof(pwms[0]); i++)
		nexus_uC_pwm_dst_load_shared(pwms[i]);
	
}

void finished(void){
	//nothing to do, let the program run
}

void processing(void){
	for(int i=0; i<sizeof(pwms)/sizeof(pwms[0]); i++)
		nexus_uC_pwm_dst_update(pwms[i], simulation_t, step_dt);
	out[0] = nexus_uC_pwm_dst_get_output(pwms[0])-1.0;
}
