#include <string.h>
#include "Framer.h"

//pPacket size : 250
//|-------------------------------------------------------------------|
//|  MHDR | DevAddr | CFtrl | Fcnt | FOpts | FPort | FRMPayload | MIC |
//|   1   |    4    |   1   |   2  |   16  |   1   |      N     |  4  |
//|-------------------------------------------------------------------|
//
//static void printPacketBuffer(uint8_t *packet, int len){
//    for(int i =0 ; i<len; i++)
//        cout<< hex << packet[i] << " ";
//    cout<<endl;
//}

bool Framer::create(uint8_t *pPacket, LoraMacHeader *MHDR, FrameHeader *FHDR,
                    uint8_t *FPort, uint8_t *Packet_length) {
    uint8_t *buffer = pPacket;

    memmove(pPacket + (FRAMER_FIELD_NoFOpts_SIZE + FHDR->FCtrl.Bits.FOptsLen), pPacket, *Packet_length);

    *buffer = MHDR->Value;
    buffer = buffer + FRAMER_MHDR_FIELD_SIZE;

    *((uint32_t *) buffer) = FHDR->DevAddr;
    buffer = buffer + FRAMER_DevAddr_FIELD_SIZE;

    *buffer = FHDR->FCtrl.Value;
    buffer = buffer + FRAMER_FCtrl_FIELD_SIZE;

    *((uint16_t *) buffer) = FHDR->FCnt;
    buffer = buffer + FRAMER_FCnt_FIELD_SIZE;

    *buffer = *FPort;
    *Packet_length += FRAMER_FIELD_NoFOpts_SIZE + FHDR->FCtrl.Bits.FOptsLen + FRAMER_MIC_FIELD_SIZE;
    return true;
}

bool Framer::parse(uint8_t *pPacket, LoraMacHeader *MHDR, FrameHeader *FHDR,
                   uint8_t *FPort, uint8_t *Packet_length) {

    checkMIC(pPacket, *Packet_length);
    uint8_t *buffer = pPacket;

    MHDR->Value = *buffer;
    buffer += FRAMER_MHDR_FIELD_SIZE;
//    memcpy(FHDR, buffer, FRAMER_FHDR_FIELD_SIZE);
//    buffer += FRAMER_FHDR_FIELD_SIZE;

    FHDR->DevAddr = *((uint32_t *) buffer);
    buffer += FRAMER_DevAddr_FIELD_SIZE;
    FHDR->FCtrl.Value = *buffer;
    buffer += FRAMER_FCtrl_FIELD_SIZE;

    FHDR->FCnt = *((uint16_t *) buffer);
    buffer += FRAMER_FCnt_FIELD_SIZE;

    memcpy(FHDR->FOpts, buffer, FHDR->FCtrl.Bits.FOptsLen);
    buffer += FHDR->FCtrl.Bits.FOptsLen;

    *FPort = *buffer;

    *Packet_length -= FRAMER_FIELD_NoFOpts_SIZE + FRAMER_MIC_FIELD_SIZE + FHDR->FCtrl.Bits.FOptsLen;
    memmove(pPacket, pPacket + FRAMER_FIELD_SIZE, *Packet_length);

    return true;
}

// TODO: MAKE MIC

uint32_t Framer::MakeMIC(uint8_t *pPacket) {
    return 0;
}

bool Framer::checkMIC(uint8_t *pPacket, uint8_t Packet_length) {
    return true;
}

bool Framer::createDataFrame(
        uint8_t *packet,
        MType mType,
        uint32_t *addr,
        uint8_t *port,
        uint8_t *FCnt,
        bool ACK,
        uint8_t *length) {

    LoraMacHeader mhdr;
    FrameHeader fhdr;

    mhdr.bits.MType = mType;
    mhdr.bits.RUF = 0;
    mhdr.bits.Major = MAJOR_VERSION;
    fhdr.DevAddr = *addr;

    if (ACK) fhdr.FCtrl.Bits.Ack = 1;
    else fhdr.FCtrl.Bits.Ack = 0;
    fhdr.FCtrl.Bits.ADR = 0;
    fhdr.FOpts = packet + (FRAMER_MHDR_FIELD_SIZE + FRAMER_FPort_FIELD_SIZE + FRAMER_DevAddr_FIELD_SIZE +
                           FRAMER_FCnt_FIELD_SIZE + FRAMER_FCtrl_FIELD_SIZE);
    fhdr.FCtrl.Bits.FOptsLen = 0; //from maccommand.cpp
//    fhdr.FOpts; // from maccommand.cpp

    fhdr.FCtrl.Bits.ADRACKReq = 0;
    fhdr.FCtrl.Bits.ClassB = 0;
    fhdr.FCnt = *FCnt;

    create(packet, &mhdr, &fhdr, port, length);

    return true;
}