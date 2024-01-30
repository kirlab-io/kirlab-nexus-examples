#include "hardware.h"
#include <nexus.h>

void* timer0;

void* pwm0;

void hardware_init(void){
	timer0 = nexus_uC_timer_create();
	pwm0 = nexus_uC_pwm_create();
	nexus_uC_pwm_set_shared_object(pwm0, nexus_pt->controller_signals.pwm_link);
}
