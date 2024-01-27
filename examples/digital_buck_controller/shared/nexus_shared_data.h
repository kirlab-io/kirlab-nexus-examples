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

static const char * NEXUS_SHARED_ID = "BUCK_DIGITAL_CONTROLLER";

typedef struct{
    volatile double output_voltage;
    volatile double output_current;
} PowerSignals;

typedef struct{
    volatile double pwm_duty_cycle;
} ControllerSignals;

typedef struct{
    PowerSignals power_signals;
    ControllerSignals controller_signals;
} NexusSharedData;

#endif
