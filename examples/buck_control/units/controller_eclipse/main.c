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
#include "nexus.h"
#include <stdio.h>
#include <stdlib.h>

#define PROCESS_SLOT (1)

/*Local process time*/
double t;

/*Buffers for shared data*/
double period = 10e-6;
double duty_cycle = 0.0;

double v_in;
double v_out;
double i_in;
double i_out;


/*Nexus callbacks*/
void write_data(void){
	nexus_pt->controller.period = period;
	nexus_pt->controller.duty_cycle = duty_cycle;
}

void read_data(void){
	v_in = nexus_pt->plant.v_in;
	i_in = nexus_pt->plant.i_in;
	v_out = nexus_pt->plant.v_out;
	i_out = nexus_pt->plant.i_out;
}

void simulation_finished(void){
    printf("\n\nSimulation finished.\n");
    exit(0);
}


/*Application*/
static const double Kp = 0.01;
static const double Ki = 0.0001;
static double i_acc = 0.0;
static double setpoint = 0.0;

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



int main(int argc, char *argv[]) {
    
	/*Nexus initialization*/
	int result = nexus_init(PROCESS_SLOT,
                            NEXUS_SHARED_ID); 

	if(result != 0) return result;
	
	nexus_set_read_callback(&read_data);
	nexus_set_write_callback(&write_data);
	nexus_set_finished_callback(&simulation_finished);
	
	
	
	t = 0.0;
	
	while(1){
		t = t+period;/*time step is switching time*/
        
        /*Play with the setpoint over time*/
        if(t<20e-3){
            setpoint = 4.0;
        } else if(t<60e-3){
            setpoint = 7.0;
        } else {
            setpoint = 4.0;
        }
        
		/*PI every switching period*/
		duty_cycle = PI((setpoint-v_out), 0.0, 0.9);
		
		nexus_sync(t);
	}
	
	return 0;
}
