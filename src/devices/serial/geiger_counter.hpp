#ifndef GEIGER_H
#define GEIGER_H

#define TTYUSB0 16

#include "serial.hpp"

class Geiger_Counter : public Serial_Device {
private:
	float voltage;
	unsigned int cpm, cps, cpm_hi, cpm_lo;

	//Private functions
	unsigned int convertReadBytes();
public:
	Geiger_Counter();
	
	//Device commands
	void reboot();	
	void turnOn();
	void turnOff();

	//Read parameters
	unsigned int readCPM();
	unsigned int readCPM_HI();
	unsigned int readCPM_LO();
	unsigned int readCPS();
	float readVoltage();

	//Getters
	float getVoltage();
	unsigned int getCPM();
	unsigned int getCPS();
	unsigned int getCPM_HI();
	unsigned int getCPM_LO();

};

#endif
