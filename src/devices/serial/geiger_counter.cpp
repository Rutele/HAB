#include "geiger_counter.hpp"
#include <unistd.h>
#include <string>

unsigned int Geiger_Counter::convertReadBytes() {
	unsigned int conv_val = 0;
	for (int i=0; i<4; ++i) conv_val = (conv_val << 8) | getBuffer()[i];
	return conv_val;
}

Geiger_Counter::Geiger_Counter() : Serial_Device(TTYUSB0, 115200), voltage(-1), cpm(0), cps(0), cpm_hi(0), cpm_lo(0) {}

void Geiger_Counter::reboot() { sendData("<REBOOT>>"); }
void Geiger_Counter::turnOn() { sendData("<POWERON>>"); }
void Geiger_Counter::turnOff() { sendData ("<POWEROFF>>");  }

unsigned int Geiger_Counter::readCPM() {
	unsigned int ret_cpm = -1;

	sendData("<GETCPM>>");
	usleep(100000);
	if (receiveData() == 4) ret_cpm = convertReadBytes();

	cpm = ret_cpm;
	return ret_cpm;
}

unsigned int Geiger_Counter::readCPM_HI() {
	unsigned int ret_cpm_h = -1;

	sendData("<GETCPMH>>");
	usleep(100000);
	if (receiveData() == 4) ret_cpm_h = convertReadBytes();

	cpm_hi = ret_cpm_h;
	return ret_cpm_h;
}

unsigned int Geiger_Counter::readCPM_LO() {
	unsigned int ret_cpm_l = -1;

	sendData("<GETCPML>>");
	usleep(100000);
	if (receiveData() == 4) ret_cpm_l = convertReadBytes();

	cpm_lo = ret_cpm_l;
	return ret_cpm_l;
}

unsigned int Geiger_Counter::readCPS() {
	unsigned int ret_cps = -1;

	sendData("<GETCPS>>");
	usleep(100000);
	if (receiveData() == 4) ret_cps = convertReadBytes();

	cps = ret_cps;
	return ret_cps;
}

float Geiger_Counter::readVoltage() {
	float ret_voltage = -1.0;

	sendData("<GETVOLT>>");
	usleep(100000);
	if (receiveData() == 5) {
		std::string tmp_str(reinterpret_cast<const char*>(getBuffer()));
		tmp_str.pop_back();
		ret_voltage = stof(tmp_str);
	}

	voltage = ret_voltage;
	return ret_voltage;
}

float Geiger_Counter::getVoltage() { return voltage; }
unsigned int Geiger_Counter::getCPM() { return cpm; }
unsigned int Geiger_Counter::getCPS() { return cps; }
unsigned int Geiger_Counter::getCPM_HI() { return cpm_hi; }
unsigned int Geiger_Counter::getCPM_LO() { return cpm_lo; }
