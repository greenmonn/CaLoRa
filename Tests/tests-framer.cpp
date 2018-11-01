#include <stdint.h>
#include "catch.hpp"
#include <iostream>
#include "Framer.h"

using namespace std;


TEST_CASE() {
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

    length = 24;

    MHDR.Value = (uint8_t) 8;
    FHDR.DevAddr = (uint32_t) 2;
    FHDR.FCtrl.Value = (uint8_t) 4;
    FHDR.FCnt = (uint16_t) 6;
    FHDR.FOpts[0] = (uint8_t) 7;
    for(int i=1;i<16;i++)
        FHDR.FOpts[i]=1;
    FPort = 3;
//|-------------------------------------------------------------------|
//|  MHDR | DevAddr | Fcnt | CFtrl | FOpts | FPort | FRMPayload | MIC |
//|   1   |    4    |  2   |   1   |   16  |   1   |      N     |  4  |
//|-------------------------------------------------------------------|

    framer.create(packetBuffer, &MHDR, &FHDR, &FPort, &length);
    LoraMacHeader MHDR_t;
    FrameHeader FHDR_t;
    uint8_t FPort_t;
    cout << "Check_point" << endl;
    for (int i = 0; i < 50; i++) {
        if(i%5==0)
            cout<<endl;
        cout<<unsigned(packetBuffer[i])<<"  ";
    }


    framer.parse(packetBuffer,&MHDR_t,&FHDR_t,&FPort_t,&length);
    REQUIRE(MHDR_t.Value == (uint8_t)8);
    REQUIRE(FPort_t == (uint8_t)3);
//    REQUIRE(FHDR_t.FCtrl.Value==(uint8_t)4);
//    REQUIRE(FHDR_t.DevAddr==(uint32_t)18);
//    REQUIRE(FHDR_t.FCnt==(uint16_t)99);
//    REQUIRE(FHDR_t.FOpts[0]==(uint8_t)3);

    //  REQUIRE(FHDR_t.FCtrl.Value==4);
}
//
//TEST_CASE("Remove Item from List", "[List]") {
//    List<uint8_t> list = List<uint8_t>();
//
//    uint8_t item = 1;
//
//    list.Add(&item);
//    list.Remove(&item);
//
//    REQUIRE(list.GetFirst() == NULL);
//
//    REQUIRE(list.Length() == 0);
//
//}