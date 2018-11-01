#include <string.h>
#include "Framer.h"
#include <iostream>
//pPacket size : 250
//|-------------------------------------------------------------------|
//|  MHDR | DevAddr | Fcnt | CFtrl | FOpts | FPort | FRMPayload | MIC |
//|   1   |    4    |  2   |   1   |   16  |   1   |      N     |  4  |
//|-------------------------------------------------------------------|

using namespace std;

bool Framer::create(uint8_t *pPacket, LoraMacHeader *MHDR,FrameHeader *FHDR,
                    uint8_t *FPort,uint8_t *length) {
    uint8_t* buffer = pPacket;

    memmove(pPacket+FRAMER_FIELD_SIZE,pPacket,*length);

    *buffer=MHDR->Value;
    buffer+=FRAMER_MHDR_FIELD_SIZE;

    *((uint32_t*)buffer)=FHDR->DevAddr;
    buffer += FRAMER_DevAddr_FIELD_SIZE;

    cout<<"FHDR->Ftrl.Value = "<<(unsigned)FHDR->FCtrl.Value<<endl;
    *buffer=FHDR->FCtrl.Value;
    buffer+=FRAMER_FCtrl_FIELD_SIZE;

    *((uint16_t*)buffer)=FHDR->FCnt;
    buffer+=FRAMER_FCnt_FIELD_SIZE;

    memcpy(buffer,FHDR->FOpts,sizeof(uint8_t)*FRAMER_FOpts_FIELD_SIZE);
    buffer+=FRAMER_FOpts_FIELD_SIZE;

    *buffer=*FPort;
     return true;
}

bool Framer::parse(uint8_t *pPacket , LoraMacHeader *MHDR,FrameHeader *FHDR,
                   uint8_t *FPort,uint8_t *Packet_length) {

    checkMIC(pPacket,*Packet_length);
    uint8_t* buffer = pPacket;

    MHDR->Value = *buffer;
    buffer += FRAMER_MHDR_FIELD_SIZE;
//    memcpy(FHDR, buffer, FRAMER_FHDR_FIELD_SIZE);
//    buffer += FRAMER_FHDR_FIELD_SIZE;

    FHDR->DevAddr=*((uint32_t*)buffer);
    buffer += FRAMER_DevAddr_FIELD_SIZE;

    FHDR->FCtrl.Value=*buffer;
    buffer +=FRAMER_FCtrl_FIELD_SIZE;

    FHDR->FCnt=*((uint16_t*)buffer);
    buffer +=FRAMER_FCnt_FIELD_SIZE;

    memcpy(FHDR->FOpts,buffer,FRAMER_FPort_FIELD_SIZE);
    buffer +=FRAMER_FOpts_FIELD_SIZE;

    *FPort = *buffer;

    *Packet_length -= FRAMER_FIELD_SIZE+FRAMER_MIC_FIELD_SIZE;
    memmove(pPacket,pPacket+FRAMER_FIELD_SIZE,*Packet_length);

    return true;
}

uint32_t Framer::MakeMIC(uint8_t *pPacket) {
    return 0;
}

bool Framer::checkMIC(uint8_t *pPacket,uint8_t Packet_length){
    return true;
}