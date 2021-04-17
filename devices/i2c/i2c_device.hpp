#include <string>

class I2C_Device {
private:
	int file_descriptor, device_address, data, write_status;
public:
	I2C_Device(int address);
	int readDevice();
	void writeReg8Bits(int reg, int d);
	void writeReg16Bits(int reg, int d);
	int readReg8Bits(int reg);
	int readReg16Bits(int reg);

private:
	void makeException(std::string &&msg);
};
