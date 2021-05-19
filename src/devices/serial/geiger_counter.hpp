#ifndef GEIGER_H
#define GEIGER_H

#define TTYUSB0 16

#include "serial.hpp"

class Geiger_Counter : public Serial_Device {
private:
	float voltage;
	unsigned int cpm, cps, cpm_hi, cpm_lo;
public:
	Geiger_Counter();
	
	//Device commands
	void reboot();	
	void turnOn();
	void turnOff();

	//Getters
	float getVoltage();
	unsigned int getCPM();
	unsigned int getCPS();
	unsigned int getCPM_HI();
	unsigned int getCPM_LO();

};

#endif
