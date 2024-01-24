/*
=========================================================================
* Copyright (C) 2024 Kirlab
*
* This file is part of KirLab Nexus.
*
* This file cannot be copied and/or distributed without the express
* permission of Kirlab.
=========================================================================
*/
 
#ifndef _NEXUS_HEADERS_H_
#define _NEXUS_HEADERS_H_

static const char * NEXUS_SHARED_ID = "BUCK_CONTROL_uC_CAN";


typedef struct{
    volatile double v_in;
    volatile double v_out;
    volatile double i_in;
    volatile double i_out;
} PowerPlantSignals;

typedef struct{
    volatile double period;
    volatile double duty_cycle;
} ControllerSignals;

typedef struct{
    Power_plant_signals_t plant;
    Controller_signals_t controller;
	NexusCanAdapter can0;
	NexusCanAdapter can1;
	NexusCanBus bus0;
} NexusSharedData;

#endif
