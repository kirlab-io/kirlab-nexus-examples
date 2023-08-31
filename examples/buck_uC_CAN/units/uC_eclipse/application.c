/*
=========================================================================
* Copyright (C) 2023 Kirlab
* All rights reserved.
*
* This file is part of KirLab Nexus.
*
* This file is distributed under the terms of KirLab Nexus license.
* Please see the EULA.txt file for the full license text.
=========================================================================
*/

#include "application.h"
#include "hardware.h"
#include <stdio.h>


//Local buffers for shared data
double period = 10e-6;
double duty_cycle = 0.0;

double v_in;
double v_out;
double i_in;
double i_out;


//Application data
long long unsigned int isr_cnt = 0;
static const double Kp = 0.01;
static const double Ki = 0.0001;
static double i_acc;
static double setpoint;

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

void application_init(void){
	i_acc = 0.0;
	setpoint = 0.0;
	configure_hardware();
}

void application_background_loop(void){
    uint32_t id;
    char data[8];
    while(read_can_message(&id, data)){
    	uint64_t fixed_comma_setpoint= *((uint64_t *)data);
    	setpoint = ((double)fixed_comma_setpoint)/(0x100000000);
    	printf("<-- id: %x   isr_cnt:%d\n", id, (int)isr_cnt);
		printf("Setpoint = %g\n", setpoint);
    }
}

void application_timer_isr(void){
	//PI every switching period
	duty_cycle = PI((setpoint-v_out), 0.0, 0.9);
	//Increment os tick counter
	isr_cnt++;

	uint32_t id = 0xCAFE;
	uint64_t * data = (uint64_t *)&v_out;
	if(isr_cnt %10 == 0){
		send_can_message(id, (const char *)data);
		printf("--> id: %x   isr_cnt:%d\n", id, (int)isr_cnt);
	}

}
