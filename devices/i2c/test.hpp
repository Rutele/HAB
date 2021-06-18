#ifndef TEST_H
#define TEST_H

#include <string>
#include "../device.hpp"

class ITEST : public Device { 
private:
	int file_descriptor, device_address, data, write_status;
  enum Measurements {T,P,H);
public:
  TEST();
  TEST(int address);
  void openDevice();
  void read_dht11_dat();
}
#endif
