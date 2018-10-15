//
// Created by Mookeun Ji on 14/10/2018.
//

#ifndef LORA_FRAMER_H
#define LORA_FRAMER_H

#include <stdint.h>

typedef struct{
		int node_id;
		int rssi;
}LoRaHeader;

class Framer {

public:
		void create(uint8_t* hdr, LoRaHeader hdr);
		LoRaHeader parse(uint8_t* hdr);

};


#endif //LORA_FRAMER_H
