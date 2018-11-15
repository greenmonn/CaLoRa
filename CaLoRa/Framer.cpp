#include <string.h>
#include "Framer.h"
//pPacket size : 250
//|-------------------------------------------------------------------|
//|  MHDR | DevAddr | FCtrl | Fcnt | FOpts | FPort | FRMPayload | MIC |
//|   1   |    4    |   1   |   2  |   15  |   1   |      N     |  4  |
//|-------------------------------------------------------------------|


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

    memcpy(buffer, FHDR->FOpts, FHDR->FCtrl.Bits.FOptsLen);
    buffer += FHDR->FCtrl.Bits.FOptsLen;

    *buffer = *FPort;
    buffer = buffer + FRAMER_FPort_FIELD_SIZE;

    //add FRMPayload length;
    buffer = buffer + *Packet_length;

    *Packet_length += FRAMER_FIELD_NoFOpts_SIZE + FHDR->FCtrl.Bits.FOptsLen;

    MakeMIC(buffer, Packet_length);

    return true;
}

bool Framer::parse(uint8_t *pPacket, LoraMacHeader *MHDR, FrameHeader *FHDR,
                   uint8_t *FPort, uint8_t *Packet_length) {
    checkMIC(pPacket, *Packet_length);
    uint8_t *buffer = pPacket;

    MHDR->Value = *buffer;
    buffer += FRAMER_MHDR_FIELD_SIZE;

    FHDR->DevAddr = *((uint32_t *) buffer);
    buffer += FRAMER_DevAddr_FIELD_SIZE;

    FHDR->FCtrl.Value = *buffer;
    buffer += FRAMER_FCtrl_FIELD_SIZE;

    FHDR->FCnt = *((uint16_t *) buffer);
    buffer += FRAMER_FCnt_FIELD_SIZE;


    memcpy(this->Fopts_temp, buffer, FHDR->FCtrl.Bits.FOptsLen);
    FHDR->FOpts=this->Fopts_temp;

    buffer += FHDR->FCtrl.Bits.FOptsLen;

    *FPort = *buffer;

    memmove(pPacket, pPacket + FRAMER_FIELD_NoFOpts_SIZE + FHDR->FCtrl.Bits.FOptsLen, *Packet_length);


    *Packet_length -= FRAMER_FIELD_NoFOpts_SIZE + FHDR->FCtrl.Bits.FOptsLen + FRAMER_MIC_FIELD_SIZE;

    return true;
}

// TODO: MAKE MIC

bool Framer::MakeMIC(uint8_t *pPacket_Buffer, uint8_t *Packet_length) {
    *(pPacket_Buffer++) = 1;
    *(pPacket_Buffer++) = 2;
    *(pPacket_Buffer++) = 3;
    *(pPacket_Buffer++) = 4;
    *Packet_length += FRAMER_MIC_FIELD_SIZE;

    return true;
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
    uint8_t fopts_out[LORA_MAC_COMMAND_MAX_FOPTS_LENGTH];
    uint8_t foptlen;
    mhdr.bits.MType = mType;
    mhdr.bits.RUF = 0;
    mhdr.bits.Major = MAJOR_VERSION;
    fhdr.DevAddr = *addr;

    fhdr.FCtrl.Bits.Ack = ACK ? 1 : 0;
    fhdr.FCtrl.Bits.ADR = 0;

    fhdr.FOpts = fopts_out;

    macCmd.InsertToFrame(fopts_out, &foptlen);

    fhdr.FCtrl.Bits.FOptsLen = foptlen;

    fhdr.FCtrl.Bits.ADRACKReq = 0;
    fhdr.FCtrl.Bits.ClassB = 0;
    fhdr.FCnt = *FCnt;

    create(packet, &mhdr, &fhdr, port, length);

    return true;
}