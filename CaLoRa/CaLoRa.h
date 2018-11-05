#ifndef LORA_CALORA_H
#define LORA_CALORA_H

#include "LoRaWan.h"
#include "ClassA.h"
#include "ClassController.h"

/*
 * CaLoRa:
 *  - CaLoRa layer implementation
 */

class CaLoRa {

private:
		recv_callback_t recvCallback;
		LoRaWan *loRaWan;

public:
		explicit CaLoRa(recv_callback_t recvCallback);
		bool init();

		void oneLoop();
		void send(uint8_t *packet, uint8_t length);
};


#endif //LORA_CALORA_H
