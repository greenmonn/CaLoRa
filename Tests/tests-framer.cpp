#include <stdint.h>
#include "catch.hpp"
#include "Framer.h"


TEST_CASE("Create and Parse", "[Framer]") {
    Framer framer;
    uint8_t packetBuffer[250];
    uint8_t length=3;
    uint32_t addr=0x0000000A;
    uint8_t port=0;
    uint8_t fcnt=0;
    bool ack=true;
    packetBuffer[0] = 254;
    packetBuffer[1] = 253;
    packetBuffer[2] = 252;

    framer.createDataFrame(packetBuffer,FRAMER_Join_Accept,&addr,&port,&fcnt,ack,&length);


    LoraMacHeader MHDR_t;
    FrameHeader FHDR_t;
    uint8_t FPort_t;

    framer.parse(packetBuffer,&MHDR_t,&FHDR_t,&FPort_t,&length);

    REQUIRE(MHDR_t.bits.MType==FRAMER_Join_Accept);
    REQUIRE(FPort_t == 0);
    REQUIRE(FHDR_t.FCtrl.Bits.Ack==1);
    REQUIRE(FHDR_t.DevAddr==0x0000000A);
    REQUIRE(FHDR_t.FCnt==0);
}