#ifndef LORA_FRAMER_H
#define LORA_FRAMER_H


/*
 * Framer:
 * 	- responsible for header creation and parsing
 */

#include <stdint.h>

typedef struct{

}LoRaHeader;

class Framer {

public:

		// insert lora headers fields for outgoing packet
		void create(uint8_t *pPacket, uint8_t *length, LoRaHeader loRaHeader);

		// parse lora headers fields for incoming packet
		LoRaHeader parse(uint8_t * pPacket);

};


#endif //LORA_FRAMER_H
