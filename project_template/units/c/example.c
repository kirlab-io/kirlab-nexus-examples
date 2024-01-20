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

#define PROCESS_SLOT (0)

/*Local process time*/
double t;
double period = 10e-6;

double b_signal_0;
double b_signal_1;


/*Nexus callbacks*/
void write_data(void){
	nexus_pt->a.signal_0 = 0.0;
	nexus_pt->a.signal_1 = 1.0;
}

void read_data(int argc, char *argv[]){
	b_signal_0 = nexus_pt->b.signal_0;
	b_signal_1 = nexus_pt->b.signal_1;
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
	
	while(1){
		t = t+period;
		
		//do some processing...
		
		nexus_sync(t);
	}
	
	return 0;
}
