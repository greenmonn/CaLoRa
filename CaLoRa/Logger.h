#ifndef LORA_LOGGER_H
#define LORA_LOGGER_H

#include "Arduino.h"

class Logger {

public:
		static void print(const char c);
		static void println(const char* string);
		static void print(const char* string);
		static void print(const char* string, const int length);

		static void printHex(const uint8_t i);
		static void printHex(const uint8_t* p, const int length);

private:
		Logger(){};
};


#endif //LORA_LOGGER_H
