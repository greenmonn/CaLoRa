#include <stdint.h>
#include "catch.hpp"
#include "Framer.h"

#include <iostream>

using namespace std;
//pPacket size : 250
//|-------------------------------------------------------------------|
//|  MHDR | DevAddr | FCtrl | Fcnt | FOpts | FPort | FRMPayload | MIC |
//|   1   |    4    |   1   |   2  |   15  |   1   |      N     |  4  |
//|-------------------------------------------------------------------|

void printHex(const uint8_t i) {

    const char hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                           '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    cout << "0x";
    cout << hexmap[i >> 4];
    cout << hexmap[i & 0x0F];
}

void printHex(const uint8_t *p, const int length) {
    for (int i = 0; i < length; i++) {
        printHex(p[i]);
        cout << "  ";
    }
    cout << endl;

}

TEST_CASE("Create", "[Framer]") {
    Framer framer;
    uint8_t packetBuffer[250];
    uint8_t length = 3;
    uint32_t addr = 0x0000000A;
    uint8_t port = 5;
    uint8_t fcnt = 3;
    bool ack = true;
    packetBuffer[0] = 254;
    packetBuffer[1] = 253;
    packetBuffer[2] = 252;

    framer.createDataFrame(packetBuffer, FRAMER_Join_Accept, &addr, &port, &fcnt, ack, &length);

    printHex(packetBuffer, length);

    LoraMacHeader MHDR_t;
    FrameHeader FHDR_t;
    uint8_t FPort_t;

    framer.parse(packetBuffer, &MHDR_t, &FHDR_t, &FPort_t, &length);

    REQUIRE(MHDR_t.bits.MType == FRAMER_Join_Accept);
    REQUIRE(FPort_t == 5);
    REQUIRE(FHDR_t.FCtrl.Bits.Ack == 1);
    REQUIRE(FHDR_t.DevAddr == 0x0000000A);
    REQUIRE(FHDR_t.FCnt == 3);
}

//Put Foptslen 5 values {1,2,3,4,5}
//TEST_CASE("Parse", "[Framer]") {
//    Framer framer;
//    uint8_t Packet[250] = {0,};
//    Packet[0] = 1;
//    Packet[1] = 0x0A;
//    Packet[5] = 0x54;
//    Packet[6] = 0x03;
//    Packet[8]= 0x01;
//    Packet[9]= 0x02;
//    Packet[10]= 0x03;
//    Packet[11]= 0x04;
//    Packet[12]= 0x05;
//    Packet[13]= 0x05;
//    Packet[14]= 0xFE;
//    Packet[15]= 0xFD;
//    Packet[16]= 0xFC;
//    uint8_t length = 21;
//
//    LoraMacHeader MHDR_t;
//    FrameHeader FHDR_t;
//    uint8_t FPort_t;
//
//    framer.parse(Packet, &MHDR_t, &FHDR_t, &FPort_t, &length);
//
//    REQUIRE(MHDR_t.bits.MType == FRAMER_Join_Accept);
//    REQUIRE(FPort_t == 5);
//    REQUIRE(FHDR_t.FCtrl.Bits.Ack == 1);
//    REQUIRE(FHDR_t.DevAddr == 0x0000000A);
//    REQUIRE(FHDR_t.FCnt == 3);
//}
