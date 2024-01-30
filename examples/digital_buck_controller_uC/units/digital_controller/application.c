#include "application.h"
#include "hardware.h"

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
static const double Kp = 0.05;
static const double Ki = 0.0005;
static const double MAX_DUTY = 0.9;
static const double MIN_DUTY = 0.1;
static const double TIMER_PERIOD = 10e-6;//10us
static const double PWM_PERIOD = 5e-6;//200kHz

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

	//timer config
	nexus_uC_timer_set_period(timer0, TIMER_PERIOD);
	nexus_uC_timer_add_event_callback(timer0, NEXUS_UC_CALLBACK(application_control_task));
	nexus_uC_timer_enable(timer0, true);//enable counting
	nexus_uC_timer_enable_event(timer0, true);//enable notifications

	//pwm config
	nexus_uC_pwm_set_period(pwm0, PWM_PERIOD);
	nexus_uC_pwm_enable(pwm0, true);
	nexus_uC_pwm_enable_output(pwm0, true);
}

void application_control_task(void){
	//PI controller
	pwm_duty_cycle = PI_step(&pi, (setpoint - output_voltage));
    nexus_uC_pwm_set_fall(pwm0, PWM_PERIOD*pwm_duty_cycle);//falling edge (rise at 0)
}

void application_background_loop(void){}
