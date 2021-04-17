#include "i2c_device.hpp"
#include <iostream>

int main() {
	I2C_Device dev(0x68);
	std::cout << dev.readDevice() << std::endl;
	return 0;
}
