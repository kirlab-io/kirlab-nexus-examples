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
#include <nexus_com.h>
#include <nexus_uC.h>
#include <nexus.h>

#define CAN_ADAPTER (&nexus_pt->can0)
#define CAN_BUS (&nexus_pt->bus0)

void * timer0;

void create_hardware(void){
	timer0 = nexus_uC_timer_create();
	nexus_can_init(CAN_ADAPTER);
	nexus_can_connect(CAN_ADAPTER, CAN_BUS);
}


void configure_hardware(void){
	nexus_uC_timer_set_limit(timer0, 10e-6);
	nexus_uC_timer_set_callback(timer0, &application_timer_isr);
	nexus_uC_timer_enable(timer0, true);
	nexus_uC_timer_int_enable(timer0, true);
}

void send_can_message(uint32_t id, const char * data){
	nexus_can_send(CAN_ADAPTER, id, data, 8);
}

bool read_can_message(uint32_t * id, char * data){
	int size;
	bool result = nexus_can_receive(CAN_ADAPTER, id, data, &size);
	return result;
}
