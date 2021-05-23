#ifndef DEVICE_H
#define DEVICE_H

#include <string>

class Device {
public:
	virtual void makeException(std::string &&msg) = 0;
	virtual void parseConfig() = 0;
};

#endif
