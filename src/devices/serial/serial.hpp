#ifndef SERIAL_H
#define SERIAL_H

#define TTYAMA0 22
#define BUFF_SIZE 4096

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
	
	void openDevice();
	void closeDevice();
	bool checkIsOpen();
	
	void readDevice();

	int getPortNumber();
	int getBaudRate();
	void setPortNumber(int p_num);
	void setBaudRate(int b_rate);

};

#endif
