#pragma once
#include <map>
#include <string>
#include <thread>
#include "ESC.h"
#include "BerryIMU.h"
#include "PID.h"
#include "KalmanFilter.h"
#include "RC.h"
#include <cmath>
#include "GPIO.h"

using namespace std;

class Quadcopter {

private:
	const double declination = 43.92 / 1000.0;

	ESC* esc;
	RC* rc;
	BerryIMU* imu;
	bool flying;

	//VALUES NEEDED FOR CALCULATIONS
	//RC values
	uint32_t* rc_values;
	uint32_t* rc_adj;

	//Angle variables
	double ra;
	double pa;

	double accel_ra;
	double accel_pa;

	//Angular velocity variables
	double rv;
	double pv;
	double yv;

	//Filter
	KalmanFilter* kalmanFilterX;
	KalmanFilter* kalmanFilterY;
	KalmanFilter* kalmanFilterZ;
	double kalmanX;
	double kalmanY;
	
	double kalmanX_value;
	double kalmanY_value;
	
	double* kalmanX_raw;
	double* kalmanY_raw;
	double* kalmanX_sorted;
	double* kalmanY_sorted;
	double* kalmanX_quartile;
	double* kalmanY_quartile;
	
	double* ra_pid_raw;
	double* ra_pid_sorted;
	double* pa_pid_raw;
	double* pa_pid_sorted;
	double* yv_pid_raw;
	double* yv_pid_sorted;

	//Roll, Pitch, Yaw PIDs
	PID ra_pid{ 7, 0, 0 };
	PID pa_pid{ 7, 0, 0 };

	//Roll, Pitch, and Yaw angular velocity PID's
	PID yv_pid{ 2, 0, 0 };

	//Raw output arrays
	double* accel_out;
	double* gyro_out;
	double* mag_out;

	//PID output arrays
	double ra_pid_out;
	double pa_pid_out;
	double yv_pid_out;

	//Time variables
	uint32_t startTime;
	uint32_t endTime;
	double dt;

public:
	Quadcopter();
	~Quadcopter();
	void print();
	void run();
};
