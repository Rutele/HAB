#include "serial.hpp"
#include "rs232.h"
#include <iostream>

void Serial_Device::onInit() {
	is_open = false;
	openDevice();
}

Serial_Device::Serial_Device() : port_number(TTYAMA0), baud_rate(9600), is_open(false) {
	onInit();
}

Serial_Device::Serial_Device(int p_num, int b_rate) : port_number(p_num), baud_rate(b_rate), is_open(false) {
	onInit();
}

void Serial_Device::openDevice() {
	RS232_OpenComport(port_number, baud_rate, "8N1", 0);
	is_open = true;
}

void Serial_Device::closeDevice() {
	RS232_CloseComport(port_number);
	is_open = false;
}

bool Serial_Device::checkIsOpen() { return is_open; }

void Serial_Device::readDevice() {
	int n = RS232_PollComport(port_number, buf, BUFF_SIZE);
	for (int i = 0; i < n; ++i) std::cout << buf[i];
	std::cout << std::endl;
}

int Serial_Device::getPortNumber() { return port_number; }
int Serial_Device::getBaudRate() { return baud_rate; }
void Serial_Device::setPortNumber(int p_num) { port_number = p_num; }
void Serial_Device::setBaudRate(int b_rate) { baud_rate = b_rate; }