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

#include <stdbool.h>
#include "application.h"
#include "hardware.h"
#include <nexus_uC.h>


/*Local buffers for shared data*/
double period = 10e-6;
double duty_cycle = 0.0;

double v_in;
double v_out;
double i_in;
double i_out;


/*Application code*/
void configure_hardware(void);

void timer_isr(void);

void pwm_isr(void);

double PI(double error, double min, double max);


long long unsigned int isr_cnt = 0;
long long unsigned int pwm_isr_cnt = 0;
static const double Kp = 0.01;
static const double Ki = 0.0001;
static double i_acc;
static double setpoint;

void application_init(void){
	/*Initialize app variables*/
	i_acc = 0.0;
	setpoint = 0.0;

	/*Initialize hardware abstraction layer*/
	configure_hardware();
}

void application_background_loop(void){
    /*Play with the setpoint over time*/
	if(isr_cnt==1){
		nexus_uC_pwm_enable_output(pwms[0], true);
	} else if(isr_cnt<200){
        setpoint = 4.0;
    } else if(isr_cnt<600){
        setpoint = 7.0;
    } else {
        setpoint = 4.0;
    }
}

double PI(double error, double min, double max){
	double new_iacc = i_acc + error*Ki;
	double out = error*Kp + new_iacc;
	if(out < min){
		out = min;
	} else if(out > max){
		out = max;
	} else {
		i_acc = new_iacc;
	}
	return out;
}

double debug_rise = 0.0;
double debug_fall = 5e-6;

void configure_hardware(void){
	//Configure timer
	nexus_uC_timer_set_period(timer0, 100e-6);
	nexus_uC_timer_add_event_callback(timer0, nexus_uC_callback(&timer_isr));
	nexus_uC_timer_enable(timer0, true);
	nexus_uC_timer_enable_event(timer0, true);

	//Configure pwm
    nexus_uC_pwm_set_period(pwms[0], period);
    nexus_uC_pwm_enable(pwms[0], true);
    nexus_uC_pwm_enable_event(pwms[0], true);
    nexus_uC_pwm_shadow_enable(pwms[0], true);
    nexus_uC_pwm_add_event_callback(pwms[0], nexus_uC_callback(&pwm_isr));

    //Start pwm with 0 duty cycle
    nexus_uC_pwm_set_rise(pwms[0], 0.0);
    nexus_uC_pwm_set_fall(pwms[0], 0.0);
}

void timer_isr(void){

	/*Increment os tick counter*/
	isr_cnt++;
}

void pwm_isr(void){
	/*PI every switching cycle*/
	duty_cycle = PI((setpoint-v_out), 0.0, 0.9);
	nexus_uC_pwm_set_fall(pwms[0], duty_cycle*period);
	pwm_isr_cnt++;
}
