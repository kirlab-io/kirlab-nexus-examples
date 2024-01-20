/*
=========================================================================
* Copyright (C) 2024 Kirlab
* All rights reserved.
*
* This file is part of KirLab Nexus.
*
* This file is distributed under the terms of KirLab Nexus license.
* Please see the EULA.txt file for the full license text.
=========================================================================
*/

#ifndef HARDWARE_H_
#define HARDWARE_H_

#define NEXUS_UC_EVENT_MAX_CALLBACKS (512)

typedef void (*callback_t)(void);


typedef struct{
    int num_callbacks;
    callback_t callbacks[NEXUS_UC_EVENT_MAX_CALLBACKS];
} NexusuCEventGenerator_t;

typedef struct{
    double cnt;
    double limit;
    bool int_enable;
    bool enabled;
    NexusuCEventGenerator_t event_generator;
} NexusuCTimer_t;


extern NexusuCTimer_t * timer0;

void create_hardware(void);

void configure_hardware(void);

#endif /* HARDWARE_H_ */
