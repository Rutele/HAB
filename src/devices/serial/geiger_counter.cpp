#include "geiger_counter.hpp"
#include "../rapidjson/document.h"
#include "../rapidjson/filereadstream.h"
#include <unistd.h>
#include <string>

#define JSON_BUFFER_SIZE 65536

unsigned int Geiger_Counter::convertReadBytes() {
	unsigned int conv_val = 0;
	for (int i=0; i<4; ++i) conv_val = (conv_val << 8) | getBuffer()[i];
	return conv_val;
}

void Geiger_Counter::parseConfig() {
	bool proper_config = false;
	std::string config_file_name = "devices_config.json";
	FILE *config_file = fopen(config_file_name.c_str(), "rb");

	if (config_file == NULL) {
		makeException("No config file found");
	}

	char json_buffer[JSON_BUFFER_SIZE];
	rapidjson::FileReadStream input_stream(config_file, json_buffer, sizeof(json_buffer));
	rapidjson::Document parsedConfig;
	parsedConfig.ParseStream<0, rapidjson::UTF8<>, rapidjson::FileReadStream>(input_stream);

	if (parsedConfig.HasMember("geiger")) {
		proper_config = true;
		if(!parsedConfig["geiger"].HasMember("port_number")) proper_config = false;
		if(!parsedConfig["geiger"].HasMember("baud_rate")) proper_config = false;
		if(!parsedConfig["geiger"].HasMember("mode")) proper_config = false;
		if(!parsedConfig["geiger"].HasMember("read_timeout")) proper_config = false;
	}

	if (!proper_config) {
		makeException("Bad config file");
	}

	setPortNumber(parsedConfig["geiger"]["port_number"].GetInt());
	setBaudRate(parsedConfig["geiger"]["baud_rate"].GetInt());
	setMode(parsedConfig["geiger"]["mode"].GetString());
	setReadTimeout(parsedConfig["geiger"]["read_timeout"].GetInt());
	openDevice();

}

Geiger_Counter::Geiger_Counter() : Serial_Device(TTYUSB0, 115200), voltage(-1), cpm(0), cps(0), cpm_hi(0), cpm_lo(0) {
	parseConfig();
}

void Geiger_Counter::reboot() { sendData("<REBOOT>>"); }
void Geiger_Counter::turnOn() { sendData("<POWERON>>"); }
void Geiger_Counter::turnOff() { sendData ("<POWEROFF>>");  }

unsigned int Geiger_Counter::readCPM() {
	unsigned int ret_cpm = -1;

	sendData("<GETCPM>>");
	usleep(getReadTimeout());
	if (receiveData() == 4) ret_cpm = convertReadBytes();

	cpm = ret_cpm;
	return ret_cpm;
}

unsigned int Geiger_Counter::readCPM_HI() {
	unsigned int ret_cpm_h = -1;

	sendData("<GETCPMH>>");
	usleep(getReadTimeout());
	if (receiveData() == 4) ret_cpm_h = convertReadBytes();

	cpm_hi = ret_cpm_h;
	return ret_cpm_h;
}

unsigned int Geiger_Counter::readCPM_LO() {
	unsigned int ret_cpm_l = -1;

	sendData("<GETCPML>>");
	usleep(getReadTimeout());
	if (receiveData() == 4) ret_cpm_l = convertReadBytes();

	cpm_lo = ret_cpm_l;
	return ret_cpm_l;
}

unsigned int Geiger_Counter::readCPS() {
	unsigned int ret_cps = -1;

	sendData("<GETCPS>>");
	usleep(getReadTimeout());
	if (receiveData() == 4) ret_cps = convertReadBytes();

	cps = ret_cps;
	return ret_cps;
}

float Geiger_Counter::readVoltage() {
	float ret_voltage = -1.0;

	sendData("<GETVOLT>>");
	usleep(getReadTimeout());
	if (receiveData() == 5) {
		std::string tmp_str(reinterpret_cast<const char*>(getBuffer()));
		tmp_str.pop_back();
		ret_voltage = stof(tmp_str);
	}

	voltage = ret_voltage;
	return ret_voltage;
}

float Geiger_Counter::getVoltage() { return voltage; }
unsigned int Geiger_Counter::getCPM() { return cpm; }
unsigned int Geiger_Counter::getCPS() { return cps; }
unsigned int Geiger_Counter::getCPM_HI() { return cpm_hi; }
unsigned int Geiger_Counter::getCPM_LO() { return cpm_lo; }
