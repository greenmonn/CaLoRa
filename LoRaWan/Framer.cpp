#include <string.h>
#include "Framer.h"

//pPacket size : 250  

//  MHDR | FHDR | FPort | FRMPayload | MIC

void Framer::create(uint8_t *pPacket, LoraMacHeader *MHDR,FrameHeader *FHDR,
                    uint8_t *FPort,uint8_t *length) {

    uint8_t buffer = 0;

    memmove(pPacket+FRAMER_FIELD_SIZE,pPacket,*length);

    memcpy(pPacket,&MHDR->Value,FRAMER_MHDR_FIELD_SIZE);
    buffer+=FRAMER_MHDR_FIELD_SIZE;

    memcpy(pPacket+buffer,&FHDR->DevAddr,FRAMER_DevAddr_FIELD_SIZE);
    buffer+=FRAMER_DevAddr_FIELD_SIZE;

    memcpy(pPacket+buffer,&FHDR->FCnt,FRAMER_FCnt_FIELD_SIZE);
    buffer+=FRAMER_FCnt_FIELD_SIZE;

    memcpy(pPacket+buffer,&FHDR->FCtrl.Value,FRAMER_FCtrl_FIELD_SIZE);
    buffer+=FRAMER_FCtrl_FIELD_SIZE;
    
    memcpy(pPacket+buffer,&FHDR->FOpts,FRAMER_FOpts_FIELD_SIZE);
    buffer+=FRAMER_FOpts_FIELD_SIZE;

    memcpy(pPacket+buffer,&FPort,FRAMER_FPort_FIELD_SIZE);
    buffer+=FRAMER_FPort_FIELD_SIZE;
 
    // buffer+=length;
    // memcpy(pPacket+buffer,MakeMIC(pPacket),FRAMER_MIC_FIELD_SIZE);
}

uint8_t Framer::parse(uint8_t *pPacket , LoraMacHeader *MHDR,FrameHeader *FHDR,
                uint8_t *FPort, uint8_t *FRMPayload,uint8_t *Packet_length) {

    checkMIC(pPacket,*Packet_length);
    memcpy(&MHDR->Value, pPacket,FRAMER_MHDR_FIELD_SIZE);
    *pPacket<<=FRAMER_MHDR_FIELD_SIZE;
    *Packet_length-=FRAMER_MHDR_FIELD_SIZE;
//
    memcpy(&FHDR->DevAddr,pPacket,FRAMER_DevAddr_FIELD_SIZE);
    *pPacket<<=FRAMER_DevAddr_FIELD_SIZE;
    *Packet_length-=FRAMER_DevAddr_FIELD_SIZE;

    memcpy(&FHDR->FCnt,pPacket,FRAMER_FCnt_FIELD_SIZE);
    *pPacket<<=FRAMER_FCnt_FIELD_SIZE;
    *Packet_length-=FRAMER_FCnt_FIELD_SIZE;

    memcpy(&FHDR->FCtrl.Value,pPacket,FRAMER_FCtrl_FIELD_SIZE);
    *pPacket<<=FRAMER_FCtrl_FIELD_SIZE;
    *Packet_length-=FRAMER_FCtrl_FIELD_SIZE;
 
    memcpy(&FHDR->FOpts,pPacket,FRAMER_FOpts_FIELD_SIZE);
    *pPacket<<=FRAMER_FOpts_FIELD_SIZE;
    *Packet_length-=FRAMER_FOpts_FIELD_SIZE;

    memcpy(&FPort,pPacket,FRAMER_FPort_FIELD_SIZE);
    *pPacket<<=FRAMER_FPort_FIELD_SIZE;
    *Packet_length-=FRAMER_FPort_FIELD_SIZE;

    memcpy(&FRMPayload,pPacket,sizeof(Packet_length)-FRAMER_MIC_FIELD_SIZE);
    //*pPacket<<=FRAMER_FPort_FIELD_SIZE;
    *Packet_length-=FRAMER_MIC_FIELD_SIZE;
    return *Packet_length;
}


uint32_t Framer::MakeMIC(uint8_t *pPacket) {
    return 0;
}

bool Framer::checkMIC(uint8_t *pPacket,uint8_t Packet_length){
    return true;
}