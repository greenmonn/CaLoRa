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
#include "MacCommand.h"

#define FRAMER_MHDR_FIELD_SIZE          1
#define FRAMER_MIC_FIELD_SIZE           4
#define FRAMER_FPort_FIELD_SIZE         1
#define FRAMER_FIELD_SIZE               24
#define FRAMER_DevAddr_FIELD_SIZE       4
#define FRAMER_FCnt_FIELD_SIZE          2
#define FRAMER_FCtrl_FIELD_SIZE         1
#define FRAMER_FIELD_NoFOpts_SIZE       9

#define MAJOR_VERSION                   0x00

//  MHDR | FHDR | FPort | FRMPayload | MIC
//LoraMacHeader | LoRaMacFCtrl | FPort | Packet | MIC

//|-------------------------------------------------------------------|
//|  MHDR | DevAddr | CFtrl | Fcnt | FOpts | FPort | FRMPayload | MIC |
//|   1   |    4    |   1   |   2  |   15  |   1   |      N     |  4  |
//|-------------------------------------------------------------------|
/*
*MType in MHDR
*3bits
*6 different Mac message types
*000: Join Request (used by OTA activation)
*001: Join Accept (used by OTA activation)
*010: Unconfirmed Data Up(do not require ack)
*011: Unconfirmed Data Down(do not require ack)
*100: Confirmed Data Up (require ack by receiver)
*101: Confirmed Data down (require ack by receiver)
*
*RFU in MHDR
*3bits
*reserved for future usage
*Major in MHDR
*2bits
*Major bits = 00 : LoRaWAN R1
*specifies the first 4bytes of the MAC Payload(DevAddr)
 */

/*Devaddr in FHDR               => used in init
* 4 Bytes
        * Address of end device
*/

/* FCtrl in FHDR               => frequently using
 * 1 Byte
 * DownLink
 * ADR RFU ACK FPending FOptsLen
 *  7   6   5     4       3~0
 * UpLink
 * ADR ADRACKReq ACK ClassB FOptsLen
 *  7      6      5    4      3~0
 */

/* FCnt in FHDR
 * 2 Bytes
 *
 *
 */

/* FOpts in FHDR
 * 15 Bytes
 *
 *
 */

/* FPort
  * 1 Bytes
  * FRMPayload is not empty,must be present
  * Value 0 == FRMPayload is MAC command
  * 1~223 are application-specific
  * 224 is LoraWan Mac layer test protocol
  * 225..255 (0xE1..0xFF) are reserved for future standardized application extensions
  */

typedef enum MessageType {

    FRAMER_Join_Request = 0x00,
    FRAMER_Join_Accept = 0x01,
    FRAMER_Unconfirmed_Data_Up = 0x02,
    FRAMER_Unconfirmed_Data_Down = 0x03,
    FRAMER_Confirmed_Data_Up = 0x04,
    FRAMER_Confirmed_Data_down = 0x05

} MType;

typedef union //8bits
{
    uint8_t Value;
    struct MHDR_bits {
        uint8_t MType:3;
        uint8_t RUF:3;
        uint8_t Major:2;
    } bits;
} LoraMacHeader;

typedef union //8bits
{
    uint8_t Value;
    struct sCtrlBits {
        uint8_t ADR             : 1;
        uint8_t RFU             : 1;
        uint8_t Ack             : 1;
        uint8_t FPending        : 1;
        uint8_t FOptsLen        : 4;  //
    } Bits;
} LoraMacFCtrl_downlink;

typedef union //8bits
{
    uint8_t Value;
    struct sCtrlBits {
        uint8_t ADR             : 1;
        uint8_t ADRACKReq       : 1;
        uint8_t Ack             : 1;
        uint8_t ClassB          : 1;
        uint8_t FOptsLen        : 4;  //
    } Bits;
} LoraMacFCtrl_uplink;

typedef struct FrameHeader {
    uint32_t DevAddr;
    LoraMacFCtrl_uplink FCtrl;
    LoraMacFCtrl_downlink FCtcl_down;
    uint16_t FCnt;
    uint8_t *FOpts;
} FrameHeader;
/*
 * TODO Join-Request , Join-Response
 */
typedef struct {
    LoraMacHeader MHDR;
    FrameHeader FHDR;
    uint8_t FPort;
    uint8_t *FRMPayload;
    uint32_t MIC;
} PHYPayload;

class Framer {

public:
    bool createDataFrame(uint8_t *packet, MType mType, uint32_t *addr, uint8_t *port, uint8_t *FCnt,
                         bool ACK, uint8_t *length);

    bool parse(uint8_t *pPacket, LoraMacHeader *MHDR, FrameHeader *FHDR, uint8_t *FPort,
               uint8_t *Packet_length);

private:

    MacCommandsContext macCmd;
    uint8_t Fopts_temp[15];

    bool create(uint8_t *pPacket, LoraMacHeader *MHDR, FrameHeader *FHDR, uint8_t *FPort,
                uint8_t *Packet_length);

    // parse lora headers fields for incoming packet
    bool MakeMIC(uint8_t *pPacket_Buffer,uint8_t *Packet_length) ;


    bool checkMIC(uint8_t *pPacket, uint8_t Packet_length);

};

#endif //LORA_FRAMER_H