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

static const char * NEXUS_SHARED_ID = "FREQUENCY_MEASUREMENT";

typedef struct{
    double generated_signal;
    double requested_frequency;
    double requested_amplitude;
    double measured_frequency;
    double measured_amplitude;
} Nexus_shared_data_t;

#endif
