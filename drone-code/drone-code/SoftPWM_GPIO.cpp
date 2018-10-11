#include <wiringPi.h>
#include <softPwm.h>
#include "SoftPWM_GPIO.h"

SoftPWM_GPIO::SoftPWM_GPIO(int bcm_pin, int _range = 100): GPIO(bcm_pin, OUTPUT, PUD_OFF){
	softPwmCreate(bcm_pin, 0, _range);
	range = _range;
	value = 0;
}

SoftPWM_GPIO::~SoftPWM_GPIO(){
	softPwmStop(bcm_pin);
	//Base Class constructor implicity called here
}

int SoftPWM_GPIO::get_duty() {
	return value / range;
}

int SoftPWM_GPIO::getRange() {
	return range;
}

void SoftPWM_GPIO::change_value(int change) {
	value += change;
	softPwmWrite(bcm_pin, value);
}

void SoftPWM_GPIO::set_value(int _value) {
	value = _value;
	softPwmWrite(bcm_pin, value);
}