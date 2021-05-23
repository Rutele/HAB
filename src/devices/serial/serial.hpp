#ifndef SERIAL_H
#define SERIAL_H

#define TTYAMA0 22
#define BUFF_SIZE 4096

#include <string>

class Serial_Device {
private:
	int port_number, baud_rate;
	bool is_open;
	unsigned char buf[BUFF_SIZE];

	//Private functions
	void onInit();

public:
	Serial_Device();
	Serial_Device(int p_num, int b_rate);
	~Serial_Device();
	
	void openDevice();
	void closeDevice();
	bool checkIsOpen();
	
	int receiveData();
	int sendData(const std::string &msg);
	int sendData(std::string &&msg);

	int getPortNumber();
	int getBaudRate();
	void setPortNumber(int p_num);
	void setBaudRate(int b_rate);
	const unsigned char* getBuffer();

};

#endif
