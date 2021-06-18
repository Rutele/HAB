//NIE PATRZEC NA TO JESZCZE

#include "test.hpp"
##include <Adafruit_MS8607.h>
#include <Adafruit_Sensor.h>
#include <cerrno>
#include <stdexcept>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAXTIMINGS	85
#define DHTPIN		7
int dht11_dat[5] = { 0, 0, 0, 0, 0 };

#define INIT_ERR "I2C device init error. "
#define READ_ERR "I2C device read error. "
#define WRITE_ERR "I2C device write error. "

TEST::TEST() : file_descriptor(-1), device_address(0), data(0), write_status(0) {}

TEST::TEST(int address) : file_descriptor(-1), device_address(address), data(0), write_status(0) {
	openDevice();
}

void TEST::openDevice() {
	file_descriptor = Adafruit_I2CDevice(device_address);
	if (file_descriptor == -1) makeException(INIT_ERR);
}
 
void read_dht11_dat()
{
	uint8_t laststate	= HIGH;
	uint8_t counter		= 0;
	uint8_t j		= 0, i;
	float	f; 
 	
	int dht11_dat[5] = {0,0,0,0,0};
	dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;
 
	pinMode( DHTPIN, OUTPUT );
	digitalWrite( DHTPIN, LOW );
	delay( 18 );
	digitalWrite( DHTPIN, HIGH );
	delayMicroseconds( 40 );
	pinMode( DHTPIN, INPUT );
 
	for ( i = 0; i < MAXTIMINGS; i++ )
	{
		counter = 0;
		while ( digitalRead( DHTPIN ) == laststate )
		{
			counter++;
			delayMicroseconds( 1 );
			if ( counter == 255 )
			{
				break;
			}
		}
		laststate = digitalRead( DHTPIN );
 
		if ( counter == 255 )
			break;
 
		if ( (i >= 4) && (i % 2 == 0) )
		{
			dht11_dat[j / 8] <<= 1;
			if ( counter > 16 )
				dht11_dat[j / 8] |= 1;
			j++;
		}
	}
 
	if ( (j >= 40) &&
	     (dht11_dat[4] == ( (dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF) ) )
	{
		f = dht11_dat[2] * 9. / 5. + 32;
		printf( "Humidity = %d.%d %% Temperature = %d.%d C (%.1f F)\n",
			dht11_dat[0], dht11_dat[1], dht11_dat[2], dht11_dat[3], f );
	}else  {
		printf( "Data not good, skip\n" );
	}
}

IMU::IMU() : I2
