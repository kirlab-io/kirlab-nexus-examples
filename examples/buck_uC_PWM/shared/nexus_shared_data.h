/*
=========================================================================
* Copyright (C) 2023 Kirlab
*
* This file is part of KirLab Nexus.
*
* This file cannot be copied and/or distributed without the express
* permission of Kirlab.
=========================================================================
*/
 
#ifndef _NEXUS_SHARED_DATA_H_
#define _NEXUS_SHARED_DATA_H_

static const char * NEXUS_SHARED_ID = "BUCK_CONTROL_uC_PWM";

typedef struct{
    volatile double v_in;
    volatile double v_out;
    volatile double i_in;
    volatile double i_out;
} Power_plant_signals_t;

typedef struct{
    Power_plant_signals_t plant;
	NexusuCPwmLink_t pwm_links[1];
} Nexus_shared_data_t;

#endif
