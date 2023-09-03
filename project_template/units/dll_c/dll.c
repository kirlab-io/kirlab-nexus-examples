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
 
#include "nexus.h"

/*in and out from nexus*/
extern double * in;
extern double * out;

/*Exported values*/
const char * nexus_get_shared_id(void){
	return NEXUS_SHARED_ID;
}
const int unit_slot = 1;
const int in_size = 2;
const int out_size = 2;

/*Exported functions*/
void write_data(void){
    nexus_pt->a.signal_0 = in[0];
    nexus_pt->a.signal_1 = in[1];
}
	
void finished(void){
	//nothing to do, let the program run
}

void processing(void){
	//Do some extra processing...
}