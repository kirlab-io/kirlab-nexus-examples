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


/*Local buffers for shared data*/
double period = 10e-6;
double duty_cycle = 0.0;

double v_in;
double v_out;
double i_in;
double i_out;


/*Application code*/
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
	/*Initialize app variables*/
	i_acc = 0.0;
	setpoint = 0.0;

	/*Initialize hardware abstraction layer*/
	configure_hardware();
}

void application_background_loop(void){
    /*Play with the setpoint over time*/
    if(isr_cnt<2000){
        setpoint = 4.0;
    } else if(isr_cnt<6000){
        setpoint = 7.0;
    } else {
        setpoint = 4.0;
    }
}

void application_timer_isr(void){
	/*PI every switching cycle*/
	duty_cycle = PI((setpoint-v_out), 0.0, 0.9);
	/*Increment os tick counter*/
	isr_cnt++;
}
