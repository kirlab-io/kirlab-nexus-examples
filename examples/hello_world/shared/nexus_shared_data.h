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

static const char * NEXUS_SHARED_ID = "HELLO_WORLD";

typedef struct{
    volatile double signal_0;
    volatile double signal_1;
} SignalBlockA;

typedef struct{
    volatile double signal_0;
    volatile double signal_1;
} SignalBlockB;

typedef struct{
    SignalBlockA a;
    SignalBlockB b;
} NexusSharedData;

#endif
