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
#include <nexus.h>
#include <stdlib.h>
#include <stdio.h>

#define PROCESS_SLOT (2)

/*Local process time*/
double t;
double period = 100e-3;


/*Nexus callbacks*/
void read_data(void){}

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
	nexus_set_finished_callback(&simulation_finished);
	
	//init ethernet interface and connect it
	nexus_eth_init(&nexus_pt->supervisor_eth0);
	nexus_eth_connect(&nexus_pt->supervisor_eth0, &nexus_pt->lan0);

	double setpoint = 0.0;

	while(1){
		t = t+period;
		//increment setpoint
		setpoint += 1.0;

		//send it over ethernet
		NexusEthMACAddress dst_mac = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB};
		nexus_eth_send(&nexus_pt->supervisor_eth0,
				dst_mac,
				(uint8_t*)(&setpoint),
				sizeof(setpoint));

		nexus_sync(t);
	}
	
	return 0;
}
