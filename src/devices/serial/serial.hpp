#ifndef SERIAL_H
#define SERIAL_H

#define TTYAMA0 22

class Serial_Device {
private:
	int port_number, baud_rate;
	bool is_open;

	//Private functions
	void onInit();

public:
	Serial_Device();
	Serial_Device(int p_num, int b_rate);
	
	void openDevice();
	void closeDevice();
	bool checkIsOpen();

	int getPortNumber();
	int getBaudRate();
	void setPortNumber(int p_num);
	void setBaudRate(int b_rate);

};

#endif
