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
#include "nexus.h"

#define PROCESS_SLOT (0)

double t;
double period = 10e-6;
double duty_cycle = 0.0;

double v_in;
double v_out;
double i_in;
double i_out;

#ifdef __cplusplus
extern "C" {
#endif
void nexus_write_shared_memory(void){
	nexus_pt->controller.period = period;
	nexus_pt->controller.duty_cycle = duty_cycle;
}

void nexus_read_shared_memory(int argc, char *argv[]){
	v_in = nexus_pt->plant.v_in;
	i_in = nexus_pt->plant.i_in;
	v_out = nexus_pt->plant.v_out;
	i_out = nexus_pt->plant.i_out;
}

void nexus_finished(void){
    printf("Simulation finished");
    exit(0);
}
#ifdef __cplusplus
}
#endif


double t = 0.0;

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
    
	int result = nexus_init(PROCESS_SLOT,
                            nexus_shared_id); 

	if(result != 0) return result;
	
	while(1){
		t = t+period;//time step here is switching time, but it could be any arbitrary value
        
        //Play with the setpoint over time
        if(t<20e-e){
            setpoint = 4.0;
        } else if(t<60e-3){
            setpoint = 7.0;
        } else {
            setpoint = 4.0;
        }
        
		//PI every switching period
		duty_cycle = PI((setpoint-v_out), 0.0, 0.9);
		
		nexus_sync(t);
	}
	
	return 0;
}
