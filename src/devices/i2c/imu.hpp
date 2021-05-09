#ifndef IMU_H
#define IMU_H

#include "i2c_device.hpp"

#define ACCEL_CONFIG 28
#define ACCEL_XOUT_H 59
#define ACCEL_XOUT_L 60
#define ACCEL_YOUT_H 61
#define ACCEL_YOUT_L 62
#define ACCEL_ZOUT_H 63
#define ACCEL_ZOUT_L 64

#define TEMP_OUT_H 65
#define TEMP_OUT_L 66

#define PWR_MGMT_1 107
#define PWR_MGMT_2 108

class IMU : public I2C_Device {
private:
	//Parameters
	int acc_x_lsb, acc_y_lsb, acc_z_lsb, acc_g_scale_factor;
	double acc_x_g, acc_y_g, acc_z_g;
	
	enum Direction {X, Y, Z};

	//Private functions
	void onInit();

	//Accelerometer functions
	int readAccelLSB(Direction d);
public:
	IMU();
	IMU(int address);

//Accelerometer functions
	void readAccelX();
	void readAccelY();
	void readAccelZ();
	void setAccelScale(int maxG);
	int getAccelX_LSB();
	int getAccelY_LSB();
	int getAccelZ_LSB();
	double getAccelX_G();
	double getAccelY_G();
	double getAccelZ_G();
};
#endif
