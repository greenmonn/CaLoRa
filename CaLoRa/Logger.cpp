#include "Logger.h"

void Logger::println(const char *string) {
	if(Serial) Serial.println(string);
}

void Logger::print(const char *string) {
	if(Serial) Serial.print(string);
}

void Logger::print(const char *string, const int length) {
	if(Serial)
		for(int i =0;i <length ; i++)
			Serial.print(string[i]);
}


void Logger::print(const char c) {
	if(Serial) Serial.print(c);
}


void Logger::printHex(const uint8_t i) {

	const char hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7',
												 '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

	if(Serial){
		Serial.print("0x");
		Serial.print(hexmap[(i & 0xF0) >> 4]);
		Serial.print(hexmap[i & 0x0F]);
	}
}

void Logger::printHex(const uint8_t *p, const int length) {
	for(int i=0; i<length; i++) {
		printHex(p[i]);
		print(' ');
	}
	println("");
}

