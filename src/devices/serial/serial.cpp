#include "serial.hpp"
#include "rs232.h"
#include <stdexcept>

Serial_Device::Serial_Device() : port_number(TTYAMA0), baud_rate(9600), is_open(false), mode("8N1"), read_timeout (500) {
}

Serial_Device::Serial_Device(int p_num, int b_rate) : port_number(p_num), baud_rate(b_rate), is_open(false), mode("8N1"), read_timeout(500) {
}

Serial_Device::~Serial_Device() {
	RS232_CloseComport(port_number);
	is_open = false;
}

void Serial_Device::makeException(std::string &&msg) {
	throw std::runtime_error(msg);
}

void Serial_Device::openDevice() {
	RS232_OpenComport(port_number, baud_rate, mode.c_str(), 0);
	is_open = true;
}

void Serial_Device::closeDevice() {
	RS232_CloseComport(port_number);
	is_open = false;
}

bool Serial_Device::checkIsOpen() { return is_open; }

int Serial_Device::receiveData() {
	return RS232_PollComport(port_number, buf, BUFF_SIZE);
}

int Serial_Device::sendData(const std::string &msg) {
	RS232_cputs(port_number, msg.c_str());
	return msg.size();
}

int Serial_Device::sendData(std::string &&msg) {
	RS232_cputs(port_number, msg.c_str());
	return msg.size();
}

int Serial_Device::getReadTimeout() { return read_timeout; }
int Serial_Device::getPortNumber() { return port_number; }
int Serial_Device::getBaudRate() { return baud_rate; }
std::string Serial_Device::getMode() { return mode; }

void Serial_Device::setReadTimeout(int t) { read_timeout = t; }

void Serial_Device::setMode(const std::string &m) {
	if (checkIsOpen()) closeDevice();
	mode = m;
}

void Serial_Device::setPortNumber(int p_num) {
	if (checkIsOpen()) closeDevice();
	port_number = p_num; 
}

void Serial_Device::setBaudRate(int b_rate) { 
	if (checkIsOpen()) closeDevice();
	baud_rate = b_rate;
}

const unsigned char* Serial_Device::getBuffer() { return buf; }
