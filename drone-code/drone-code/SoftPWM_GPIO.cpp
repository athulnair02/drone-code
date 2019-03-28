#include <wiringPi.h>
#include <softPwm.h>
#include "SoftPWM_GPIO.h"

SoftPWM_GPIO::SoftPWM_GPIO(int bcm_pin): GPIO(bcm_pin, OUTPUT){
	softPwmCreate(bcm_pin, 0, 100);
	value = 0;
}

SoftPWM_GPIO::~SoftPWM_GPIO(){
	softPwmStop(bcm_pin);
	//Base Class constructor implicity called here
}

void SoftPWM_GPIO::setValue(int _value) {
	value = _value;
	softPwmWrite(bcm_pin, value);
}