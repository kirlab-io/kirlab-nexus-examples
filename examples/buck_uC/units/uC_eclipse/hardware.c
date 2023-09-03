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

#include <nexus_uC.h>
#include "application.h"
#include <stdbool.h>

void * timer0;

void create_hardware(void){
	(void)NEXUS_SHARED_ID;//remove warning
	timer0 = nexus_uC_timer_create();
}


void configure_hardware(void){
	nexus_uC_timer_set_limit(timer0, 10e-6);
	nexus_uC_timer_set_callback(timer0, &application_timer_isr);
	nexus_uC_timer_enable(timer0, true);
	nexus_uC_timer_int_enable(timer0, true);
}
