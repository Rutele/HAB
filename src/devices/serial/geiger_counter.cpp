#include "geiger_counter.hpp"

Geiger_Counter::Geiger_Counter() : Serial_Device(TTYUSB0, 115200), voltage(-1), cpm(0), cps(0), cpm_hi(0), cpm_lo(0) {}

void Geiger_Counter::reboot() { sendData("<REBOOT>>"); }
void Geiger_Counter::turnOn() { sendData("<POWERON>>"); }
void Geiger_Counter::turnOff() { sendData ("<POWEROFF>>");  }


float Geiger_Counter::getVoltage() { return voltage; }
unsigned int Geiger_Counter::getCPM() { return cpm; }
unsigned int Geiger_Counter::getCPS() { return cps; }
unsigned int Geiger_Counter::getCPM_HI() { return cpm_hi; }
unsigned int Geiger_Counter::getCPM_LO() { return cpm_lo; }
