#include <stdint.h>
#include "catch.hpp"

#include "MacCommand.h"

TEST_CASE("Add mac command to current context", "[MacCommand]") {
    MacCommandsContext currentContext = MacCommandsContext();

    uint8_t macCommandPayload[2] = { 0x00, 0x00 };
    size_t payloadSize = 2;

    LoRaMacCommandStatus status = currentContext.AddCommand(0x1, macCommandPayload, payloadSize);
    
    REQUIRE(status == LORAMAC_COMMANDS_SUCCESS);
}
