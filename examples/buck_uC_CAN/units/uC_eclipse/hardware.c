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

#include "hardware.h"
#include "application.h"
#include <stdbool.h>
#include <nexus_comm.h>
#include <nexus_uC.h>
#include <nexus.h>

#define CAN_ADAPTER (&nexus_pt->can0)
#define CAN_BUS (&nexus_pt->bus0)

void * timer0;

void create_hardware(void){
	(void)NEXUS_SHARED_ID;//remove warning
	timer0 = nexus_uC_timer_create();
	nexus_can_init(CAN_ADAPTER);
	nexus_can_connect(CAN_ADAPTER, CAN_BUS);
}


void send_can_message(uint32_t id, const char * data){
	nexus_can_send(CAN_ADAPTER, id, data, 8);
}

bool read_can_message(uint32_t * id, char * data){
	int size;
	bool result = nexus_can_receive(CAN_ADAPTER, id, data, &size);
	return result;
}

bool can_messages_available(void){
	return nexus_can_frames_available(CAN_ADAPTER);
}
