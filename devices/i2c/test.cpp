//NIE PATRZEC NA TO JESZCZE

#include "test.hpp"
##include <Adafruit_MS8607.h>
#include <Adafruit_Sensor.h>
#include <cerrno>
#include <stdexcept>
#include <string>
#include <cstring>

#define INIT_ERR "I2C device init error. "
#define READ_ERR "I2C device read error. "
#define WRITE_ERR "I2C device write error. "

TEST::TEST() : file_descriptor(-1), device_address(0), data(0), write_status(0) {}

TEST::TEST(int address) : file_descriptor(-1), device_address(address), data(0), write_status(0) {
	openDevice();
}

void TEST::openDevice() {
	file_descriptor = Adafruit_I2CDevice(device_address);
	if (file_descriptor == -1) makeException(INIT_ERR);
}

int TEST::ReadMeasurements(Measurements d) {
	int acc_reading_h = 0;
	int acc_reading_l = 0;
	switch (d) {
		case P:
			acc_reading_h = readReg8Bits(ACCEL_XOUT_H);
			acc_reading_l = readReg8Bits(ACCEL_XOUT_L);
			break;
		case T:
			acc_reading_h = readReg8Bits(ACCEL_YOUT_H);
			acc_reading_l = readReg8Bits(ACCEL_YOUT_L);
			break;
		case H:
			acc_reading_h = readReg8Bits(ACCEL_ZOUT_H);
			acc_reading_l = readReg8Bits(ACCEL_ZOUT_L);
			break;
	}
	return ((acc_reading_h << 8) | (acc_reading_l));
}

IMU::IMU() : I2
