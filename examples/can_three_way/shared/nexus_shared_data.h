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

const char * nexus_shared_id = "CAN_THREE_WAY";

typedef struct{
	NexusCanAdapter can0;
	NexusCanAdapter can1;
	NexusCanAdapter can2;
	NexusCanBus bus0;
} Nexus_shared_data_t;

#endif