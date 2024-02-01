#ifndef HARDWARE_H
#define HARDWARE_H

#include <nexus_uC.h>
#include <nexus_comm.h>

extern void* timer0;

extern void* pwm0;

void hardware_init(void);

size_t eth_frames_available(void);

void eth_send(NexusEthMACAddress dst, const uint8_t* data, size_t size);

void eth_receive(NexusEthMACAddress* src,
		         NexusEthMACAddress* dst,
				 uint8_t* data,
				 size_t* size);

#endif
