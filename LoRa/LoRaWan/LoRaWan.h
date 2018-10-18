#ifndef LORA_LORAMAC_H
#define LORA_LORAMAC_H

#include <SPI.h>

#include "RH_RF95.h"
#include "LoRaClass.h"
#include "SendQueue.h"


/*
 * LoRaWan:
 * 	LoRaWan(mac layer) implementation
 */

class LoRaWan {

private:
		static RH_RF95 rf95;									// radio driver
		static LoRaClass currentClass;				// current lora class - not used for now
		static SendQueue sendQueue;

		// ADR(adaptive data rate). get next data rate from existing radio state
		static int getNextDataRate();



		// hidden constructor
		LoRaWan();

		typedef void(*recv_callback_t)(uint8_t*, int);

public:
		// class related methods
		static LoRaClass getCurrentClass();
		static void changeClass(LoRaClass);

		// application interface
		static bool init(float frequency);
		static bool setRecvCallback(recv_callback_t recvCallback);
		static bool requestSend(uint8_t*, int);

		// main lorawan loop
		static void oneLoop();
};

#endif //LORA_LORAMAC_H
