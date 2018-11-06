#include <stdint.h>
#include "catch.hpp"
#include "Framer.h"

using namespace std;


TEST_CASE("Create and Parse", "[Framer]") {
    Framer framer;
    uint8_t packetBuffer[250];
    uint8_t length;
    LoraMacHeader MHDR;
    FrameHeader FHDR;
    uint8_t FPort;
    packetBuffer[0] = 254;
    packetBuffer[1] = 253;
    packetBuffer[2] = 252;
    for (int i = 3; i < 250; i++) {
        packetBuffer[i]=0;
    }

    length = 3;

    //insert data
    MHDR.Value = 8;
    FHDR.DevAddr = 0x0A0B0C0D;
    FHDR.FCtrl.Value = 10;
    FHDR.FCnt = 0x0D0C;
    FHDR.FOpts[0] = (uint8_t) 7;
    for(int i=1;i<16;i++)
        FHDR.FOpts[i]=1;
    FPort = 3;

    framer.create(packetBuffer, &MHDR, &FHDR, &FPort, &length);

    LoraMacHeader MHDR_t;
    FrameHeader FHDR_t;
    uint8_t FPort_t;

    framer.parse(packetBuffer,&MHDR_t,&FHDR_t,&FPort_t,&length);
    REQUIRE(MHDR_t.Value == 8);
    REQUIRE(FPort_t == 3);
    REQUIRE(FHDR_t.FCtrl.Value==10);
    REQUIRE(FHDR_t.DevAddr==0x0A0B0C0D);
    REQUIRE(FHDR_t.FCnt==0x0D0C);
    REQUIRE(FHDR_t.FOpts[0]==7);


}