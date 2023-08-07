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

const char * nexus_shared_id = "FREQUENCY_MEASUREMENT";

typedef struct{
    double generated_signal;
    double requested_frequency;
    double requested_amplitude;
    double measured_frequency;
    double measured_amplitude;
} Nexus_shared_data_t;

#endif
