#include <stdint.h>
#include "catch.hpp"

#include "SendQueue.h"

TEST_CASE("Push Message To Queue", "[SendQueue]") {
    SendQueue sendQueue = SendQueue();

    uint8_t message[10] = "test";

    uint8_t originalLength = sendQueue.length();

    sendQueue.push(message, 10);

    REQUIRE(sendQueue.length() - originalLength == 1);
}

TEST_CASE("Pop Message From Queue", "[SendQueue]") {
    SendQueue sendQueue = SendQueue();

    uint8_t message[10] = "test";
    sendQueue.push(message, 10);

    uint8_t buffer[10];
    uint8_t length;

    sendQueue.pop(buffer, &length);

    REQUIRE(buffer[0] == message[0]);
    REQUIRE(buffer[9] == message[9]);

    REQUIRE(length == 10);

    REQUIRE(sendQueue.length() == 0);
}
