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
 
#ifndef _NEXUS_SHARED_DATA_H_
#define _NEXUS_SHARED_DATA_H_

static const char * NEXUS_SHARED_ID = "BUCK_CONTROL";

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
    PowerPlantSignals plant;
    ControllerSignals controller;
} NexusSharedData;

#endif
