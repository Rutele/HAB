#ifndef I2C_DEVICE_H
#define I2C_DEVICE_H

#include <string>
#include "../device.hpp"

class I2C_Device : public Device { 
private:
	int file_descriptor, device_address, data, write_status;
public:
	I2C_Device();
	I2C_Device(int address);
	void openDevice();
	int readDevice();
	void writeReg8Bits(int reg, int d);
	void writeReg16Bits(int reg, int d);
	int readReg8Bits(int reg);
	int readReg16Bits(int reg);
	void makeException(std::string &&msg) override;
	void setAdress(int add);
};

#endif
