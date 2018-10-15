#ifndef LORA_LORAMAC_H
#define LORA_LORAMAC_H

/*
 * static class LoRaWan mac layer implementation
 */

#include <SPI.h>
#include <RH_RF95.h>
#include "LoRaClass.h"

// types
typedef void(*recv_callback_t)(uint8_t*, int);

// This class is meant to be used as static class
class LoRaWan {

private:
		static RH_RF95 rf95;
		static bool receiving;
		static LoRaClass currentClass;

		static int getNextDataRate(/* rssi */);

		// LoRa primitive methods
		static bool send();

		// hidden constructor
		LoRaWan();


public:
		// class related methods
		static LoRaClass getCurrentClass();
		static void changeClass(LoRaClass);

		// application interface
		static bool init(float frequency);
		static bool setRecvCallback(recv_callback_t);
		static bool requestSend(uint8_t*, int);
		static void oneLoop();
};


#endif //LORA_LORAMAC_H
