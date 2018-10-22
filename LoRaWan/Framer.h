#ifndef LORA_FRAMER_H
#define LORA_FRAMER_H


/*
 * Framer:
 * 	- responsible for header creation and parsing
 */

#include <stdint.h>

typedef struct {

	uint8_t value;

	struct MHDR_bits {
		uint8_t Major:2;
		uint8_t RUF:3;
		uint8_t MType:3;
	} bits;

} LoraMacHeader;

class Framer {

public:

		// insert lora headers fields for outgoing packet
		void create(uint8_t* pPacket, LoraMacHeader loRaHeader);

		// parse lora headers fields for incoming packet
		LoraMacHeader parse(uint8_t * pPacket);

};


#endif //LORA_FRAMER_H
