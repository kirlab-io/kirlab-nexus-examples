#include "hardware.h"
#include <nexus.h>

void* timer0;

void* pwm0;

const NexusEthMACAddress LOCALHOST_MAC = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB};

void hardware_init(void){
	timer0 = nexus_uC_timer_create();
	pwm0 = nexus_uC_pwm_create();

	nexus_eth_init(&nexus_pt->controller_eth0);
	nexus_eth_set_mac(&nexus_pt->controller_eth0, LOCALHOST_MAC);
	nexus_eth_connect(&nexus_pt->controller_eth0, &nexus_pt->lan0);
}

size_t eth_frames_available(void){
	return nexus_eth_frames_available(&nexus_pt->controller_eth0);
}

void eth_send(NexusEthMACAddress dst, const uint8_t* data, size_t size){
	nexus_eth_send(&nexus_pt->controller_eth0,
				   dst,
				   data,
				   size);
}

void eth_receive(NexusEthMACAddress* src,
				 NexusEthMACAddress* dst,
				 uint8_t* data,
				 size_t* size){
	nexus_eth_receive(&nexus_pt->controller_eth0,
					  src,
					  dst,
					  data,
					  size);
}
