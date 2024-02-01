#ifndef APPLICATION_H
#define APPLICATION_H

//imported signals
extern double output_voltage;

//exported signals
extern double pwm_duty_cycle;

//callbacks
void application_init(void);

void application_background_loop(void);

void application_control_task(void);

#endif
