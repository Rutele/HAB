#include "i2c_device.hpp"
#include <wiringPiI2C.h>
#include <cerrno>
#include <stdexcept>
#include <string>
#include <cstring>

#define INIT_ERR "I2C device init error. "
#define READ_ERR "I2C device read error. "
#define WRITE_ERR "I2C device write error. "

I2C_Device::I2C_Device() : file_descriptor(-1), device_address(0), data(0), write_status(0) {}

I2C_Device::I2C_Device(int address) : file_descriptor(-1), device_address(address), data(0), write_status(0) {
	openDevice();
}

void I2C_Device::openDevice() {
	file_descriptor = wiringPiI2CSetup(device_address);
	if (file_descriptor == -1) makeException(INIT_ERR);
}

int I2C_Device::readDevice() {
	data = wiringPiI2CRead(file_descriptor);
	if (data < 0) makeException(READ_ERR);
	else return data;	
}

void I2C_Device::writeReg8Bits(int reg, int d) {
	write_status = wiringPiI2CWriteReg8(file_descriptor, reg, d);
	if (write_status < 0) makeException(WRITE_ERR);
}

void I2C_Device::writeReg16Bits(int reg, int d) {
	write_status = wiringPiI2CWriteReg16(file_descriptor, reg, d);
	if (write_status < 0) makeException(WRITE_ERR);
}

int I2C_Device::readReg8Bits(int reg) {
	data = wiringPiI2CReadReg8(file_descriptor, reg);
	if (data < 0) makeException(READ_ERR);
	else return data;
}

int I2C_Device::readReg16Bits(int reg) {
	data == wiringPiI2CReadReg8(file_descriptor, reg);
	if (data < 0) makeException(READ_ERR);
	else return data;
}

void I2C_Device::makeException(std::string &&msg)  {
	std::string err_str = msg + std::string(std::strerror(errno));
	throw std::runtime_error(msg);
}

void I2C_Device::setAdress(int add) { device_address = add; }
