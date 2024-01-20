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
#include "nexus_comm.h"
#include "nexus.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PROCESS_SLOT (0)
#define CAN_ADAPTER (&nexus_pt->can0)
#define CAN_BUS (&nexus_pt->bus0)

/*Local process time*/
double t;
double period = 100e-6;

/*Nexus callbacks*/
void simulation_finished(void){
	printf("\n\nSimulation finished.\n");
    exit(0);
}


/*Local application*/
void init_can(void){
	nexus_can_init(CAN_ADAPTER);
	nexus_can_connect(CAN_ADAPTER, CAN_BUS);
}

void send(uint32_t id, uint8_t *data) {
    nexus_can_send(CAN_ADAPTER, id, data, 8);
    printf("-> (t = %.4f)\t%02x [ ", t, id);
    for(int i = 0; i < 8; i++) {
        printf("%02x ", data[i]);
    }
    printf("]\n");
}

void receive_all(void) {
    uint32_t id;
    uint8_t data[8];
    uint32_t size;

    while(nexus_can_frames_available(CAN_ADAPTER)) {
		nexus_can_receive(CAN_ADAPTER, &id, data, &size);
        printf("<- (t = %.4f)\t%02x [ ", t, id);
        for(int i = 0; i < 8; i++) {
            printf("%02x ", data[i]);
        }
        printf("]\n");
    }
}


int main(int argc, char *argv[]) {
    
	/*Nexus initialization*/
    int result = nexus_init(PROCESS_SLOT,
                            NEXUS_SHARED_ID);     
    if(result != 0) return result;
	
	nexus_set_finished_callback(&simulation_finished);
	
	
	init_can();
    
	uint8_t data [] = {0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8};
	
    printf("ProcessA\n");
    while(1){
        t = t+period;
        nexus_sync(t);
		
		send(0xA, data);
		receive_all();
		
		for(int i=0; i<8; i++)
			data[i] = ((data[i]+1)|0xF0) & 0xAF;
    }
    
    return 0;
}
