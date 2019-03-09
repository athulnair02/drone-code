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

using namespace std;

class Quadcopter {

private:
	const double declination = 43.92 / 1000.0;

	map<string, ESC*> motors;
	BerryIMU* imu;
	RC* rc = new RC();

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

	//Roll, Pitch, Yaw PIDs
	PID ra_pid{ .01, .01, .01 };
	PID pa_pid{ .01, .01, .01 };

	//Roll, Pitch, and Yaw angular velocity PID's
	PID yv_pid{ .01, .01, .01 };

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
