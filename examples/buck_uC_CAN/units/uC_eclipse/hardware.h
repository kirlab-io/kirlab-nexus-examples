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

#include <stdint.h>
#include <stdbool.h>

extern void * timer0;

void create_hardware(void);

void send_can_message(uint32_t id, const char * data);

bool read_can_message(uint32_t * id, char * data);

bool can_messages_available(void);

#endif /* HARDWARE_H_ */
