#ifndef SERIAL_H
#define SERIAL_H

#define TTYAMA0 22
#define BUFF_SIZE 4096

#include "../device.hpp"
#include <string>

class Serial_Device : public Device {
private:
	int port_number, baud_rate, read_timeout;
	bool is_open;
	unsigned char buf[BUFF_SIZE];
	std::string mode; 
public:
	Serial_Device();
	Serial_Device(int p_num, int b_rate);
	~Serial_Device();

	void makeException(std::string &&msg) override;
	
	void openDevice();
	void closeDevice();
	bool checkIsOpen();
	
	int receiveData();
	int sendData(const std::string &msg);
	int sendData(std::string &&msg);
	
	int getReadTimeout();
	int getPortNumber();
	int getBaudRate();
	std::string getMode();
	
	void setReadTimeout(int t);
	void setMode(const std::string &m);
	void setPortNumber(int p_num);
	void setBaudRate(int b_rate);
	const unsigned char* getBuffer();

};

#endif
