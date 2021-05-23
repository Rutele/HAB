#include "imu.hpp"
#include <iostream>

void IMU::onInit() {
	setAccelScale(2);
}

int IMU::readAccelLSB(Direction d) {
	int acc_reading_h = 0;
	int acc_reading_l = 0;
	switch (d) {
		case X:
			acc_reading_h = readReg8Bits(ACCEL_XOUT_H);
			acc_reading_l = readReg8Bits(ACCEL_XOUT_L);
			break;
		case Y:
			acc_reading_h = readReg8Bits(ACCEL_YOUT_H);
			acc_reading_l = readReg8Bits(ACCEL_YOUT_L);
			break;
		case Z:
			acc_reading_h = readReg8Bits(ACCEL_ZOUT_H);
			acc_reading_l = readReg8Bits(ACCEL_ZOUT_L);
			break;
	}
	return ((acc_reading_h << 8) | (acc_reading_l));
}

IMU::IMU() : I2C_Device(0x68) {
	onInit();
}

IMU::IMU(int address) : I2C_Device(address) {
	onInit();
}

void IMU::readAccelX() {
	acc_x_lsb = readAccelLSB(X);
	acc_x_g = (static_cast<double>(acc_x_lsb) / static_cast<double>(acc_g_scale_factor)); 
}


void IMU::readAccelY() {
	acc_y_lsb = readAccelLSB(Y);
	acc_y_g = (static_cast<double>(acc_y_lsb) / static_cast<double>(acc_g_scale_factor)); 
}

void IMU::readAccelZ() {
	acc_z_lsb = readAccelLSB(Z);
	acc_z_g = (static_cast<double>(acc_z_lsb) / static_cast<double>(acc_g_scale_factor)); 
}

void IMU::setAccelScale(int maxG) {
	int prev_reg = readReg8Bits(ACCEL_CONFIG);
	if (maxG == 4) {
		writeReg8Bits(ACCEL_CONFIG, (prev_reg | 0x8));
		acc_g_scale_factor = 8192;
	}
	else if (maxG == 8) {
		writeReg8Bits(ACCEL_CONFIG, (prev_reg | 0x10));
		acc_g_scale_factor = 4096;
	}
	else if (maxG == 16) {
		writeReg8Bits(ACCEL_CONFIG, (prev_reg | 0x18));
		acc_g_scale_factor = 2048;
	}
	else {
		writeReg8Bits(ACCEL_CONFIG, (prev_reg | 0x0));
		acc_g_scale_factor = 16384;
	}
}

int IMU::getAccelX_LSB() { return acc_x_lsb; }
int IMU::getAccelY_LSB() { return acc_y_lsb; }
int IMU::getAccelZ_LSB() { return acc_z_lsb; }
double IMU::getAccelX_G() { return acc_x_g; }
double IMU::getAccelY_G() { return acc_y_g; }
double IMU::getAccelZ_G() { return acc_z_g; }

