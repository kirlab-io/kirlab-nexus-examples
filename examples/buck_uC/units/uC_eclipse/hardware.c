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
#include "hardware.h"
#include <stdbool.h>




NexusuCTimer_t * timer0;

void create_hardware(void){
	timer0 = (NexusuCTimer_t *)nexus_uC_timer_create();
}

