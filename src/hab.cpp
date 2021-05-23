#include <iostream>
#include "devices/serial/geiger_counter.hpp"
#include "devices/i2c/imu.hpp"

int main() {
	IMU i;
	Geiger_Counter gc;
	std::cout << "Geiger volt: " << gc.readVoltage() << std::endl;
	i.readAccelX();
	std::cout << "IMU X ACC: " << i.getAccelX_G() << std::endl;
	return 0;
}
