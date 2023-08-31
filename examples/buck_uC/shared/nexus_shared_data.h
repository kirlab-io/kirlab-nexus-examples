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
 
#ifndef _NEXUS_HEADERS_H_
#define _NEXUS_HEADERS_H_

const char * nexus_shared_id = "BUCK_CONTROL_uC";



typedef struct{
    volatile double v_in;
    volatile double v_out;
    volatile double i_in;
    volatile double i_out;
} Power_plant_signals_t;

typedef struct{
    volatile double period;
    volatile double duty_cycle;
} Controller_signals_t;

typedef struct{
    Power_plant_signals_t plant;
    Controller_signals_t controller;
} Nexus_shared_data_t;

#endif
