#include "application.h"

//Input signals
double output_voltage;

//Output signals
double pwm_duty_cycle;

//PI
typedef struct{
	double Kp;
	double Ki;
	double I;
	double max_out;
	double min_out;
} PI_data_t;

double PI_step(PI_data_t* pi, double error){
	//compute P+I
	double P = pi->Kp * error;
	pi->I += pi->Ki * error;
	double out = P + pi->I;

	//anti-windup
	if(out > pi->max_out){
		out = pi->max_out;
		pi->I = pi->max_out - P;
	} else if(out < pi->min_out){
		out = pi->min_out;
		pi->I = pi->min_out - P;
	}

	return out;
}

//Control data
static const double Kp = 0.01;
static const double Ki = 0.0001;
static const double MAX_DUTY = 0.9;
static const double MIN_DUTY = 0.1;

static double setpoint;
static PI_data_t pi;

void application_init(void){
	pwm_duty_cycle = 0.0;
	setpoint = 3.3;

	pi = (PI_data_t){
		.Kp = Kp,
		.Ki = Ki,
		.I = 0.0,
		.max_out = MAX_DUTY,
		.min_out = MIN_DUTY
	};
}

void application_task(void){
	//PI controller
	pwm_duty_cycle = PI_step(&pi, (setpoint - output_voltage));
}
