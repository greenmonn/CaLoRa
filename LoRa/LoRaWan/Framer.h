#ifndef LORA_FRAMER_H
#define LORA_FRAMER_H

#include <stdint.h>

typedef struct{

}LoRaHeader;

class Framer {

public:
		void create(uint8_t* pHdr, LoRaHeader header);
		LoRaHeader parse(uint8_t* hdr);

};


#endif //LORA_FRAMER_H
