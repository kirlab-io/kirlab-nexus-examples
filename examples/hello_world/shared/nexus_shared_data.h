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

static const char * NEXUS_SHARED_ID = "HELLO_WORLD";

typedef struct{
    volatile double signal_0;
    volatile double signal_1;
} Signal_block_a_t;

typedef struct{
    volatile double signal_0;
    volatile double signal_1;
} Signal_block_b_t;

typedef struct{
    Signal_block_a_t a;
    Signal_block_b_t b;
} Nexus_shared_data_t;

#endif
