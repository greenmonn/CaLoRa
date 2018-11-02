#ifndef LORA_FRAMER_H
#define LORA_FRAMER_H


/*
 * Framer:
 * 	- responsible for header creation and parsing
 */

//Max Payload M = 230
//Max Payload N = 222
//repeater compatible

//Max Payload M = 250
//Max Payload N = 242
//not repeater compatible

#include <stdint.h>
// All Size is Byte
#define FRAMER_MHDR_FIELD_SIZE      1
#define FRAMER_FHDR_FIELD_SIZE      23
#define FRAMER_MIC_FIELD_SIZE       4
#define FRAMER_FPort_FIELD_SIZE     1
#define FRAMER_FIELD_SIZE           25
#define FRAMER_DevAddr_FIELD_SIZE   4 
#define FRAMER_FCnt_FIELD_SIZE      2
#define FRAMER_FCtrl_FIELD_SIZE     1
#define FRAMER_FOpts_FIELD_SIZE     16


//  MHDR | FHDR | FPort | FRMPayload | MIC
// LoraMacHeader | LoRaMacFCtrl | FPort | Packet | MIC

typedef union //8bits
{
	uint8_t Value;
    struct MHDR_bits {
        uint8_t Major:2;
        uint8_t RUF:3;
        uint8_t MType:3;
    } bits;
}LoraMacHeader;

typedef union //8bits
{
    uint8_t Value;
    struct sCtrlBits
    {
        uint8_t ADR             : 1;
        uint8_t RFU             : 1;
        uint8_t Ack             : 1;
        uint8_t FPending        : 1;
        uint8_t FOptsLen        : 4;  //
    }Bits;
}LoraMacFCtrl;

typedef struct  FrameHeader{
    uint32_t DevAddr;
    LoraMacFCtrl FCtrl;
    uint16_t FCnt;
    uint8_t FOpts[16];
}FrameHeader;
/*
 * TODO Join-Request , Join-Response
 */
typedef struct{
    LoraMacHeader MHDR;
    FrameHeader FHDR;
    uint8_t FPort;
    uint8_t* FRMPayload;
    uint32_t MIC;
}PHYPayload;

class Framer {

public:
    bool create(uint8_t *pPacket, LoraMacHeader *MHDR,FrameHeader *FHDR,uint8_t *FPort,
                uint8_t *length);
    // parse lora headers fields for incoming packet
    bool parse(uint8_t *pPacket , LoraMacHeader *MHDR , FrameHeader *FHDR , uint8_t *FPort ,
                 uint8_t *Packet_length);
    uint32_t MakeMIC(uint8_t* pPacket);
    bool checkMIC(uint8_t* pPacket,uint8_t Packet_length);
};
#endif //LORA_FRAMER_H