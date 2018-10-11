#include <wiringPi.h>
#include <softPwm.h>
#include "ESC_Controller.h"

//Promise
double map(double value, double lowRange1, double highRange1, double lowRange2, double highRange2);

ESC_Controller::ESC_Controller(int BCM_pin) {
	//Setup soft PWM on passed pin with a range of 100 (must contain 10-20)
	pin = new SoftPWM_GPIO(BCM_pin, 100);

	//WiringPi delays by value * 100
	lowRange = MIN_PULSE_WIDTH / 100;
	highRange = MAX_PULSE_WIDTH / 100;

	speed = 0;
}

ESC_Controller::~ESC_Controller() {
	delete pin;
}

//Speed comes in between 0-100
void ESC_Controller::setSpeed(int _speed) {
	speed = _speed;
	double value = map(speed, 0, 100, lowRange, highRange);
	pin->set_value(value);
}

int ESC_Controller::getSpeed() {
	return speed;
}


double map(double value, double lowRange1, double highRange1, double lowRange2, double highRange2) {
	double slope = (highRange2 - highRange1) / (lowRange2 - lowRange2);
	return lowRange2 + (slope * (value - lowRange1));
}