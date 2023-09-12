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
#include <nexus.h>



NexusuCTimer_t * timer0;

void * pwms[1];

void create_hardware(void){
	timer0 = (NexusuCTimer_t *)nexus_uC_timer_create();

    for(int i=0; i<sizeof(pwms)/sizeof(pwms[0]); i++){
        pwms[i] = nexus_uC_pwm_create();
        nexus_uC_pwm_set_shared_object(pwms[i], (void *)&nexus_pt->pwm_links[i]);
        nexus_uC_pwm_set_all_pwms(pwms[i], pwms, sizeof(pwms)/sizeof(pwms[0]));
    }
}

