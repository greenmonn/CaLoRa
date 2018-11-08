#include <stdint.h>
#include "catch.hpp"

#include "MacCommand.h"

TEST_CASE("Add mac command to current context", "[MacCommand]") {
    MacCommandsContext currentContext = MacCommandsContext();

    LoRaMacServerCommand commandID = SRV_MAC_LINK_ADR_REQ;
    uint8_t macCommandPayload[2] = { 0x00, 0x00 };
    size_t payloadSize = 2;

    LoRaMacCommandStatus status = currentContext.AddCommand(commandID, macCommandPayload, payloadSize);

    REQUIRE(status == LORAMAC_COMMANDS_SUCCESS);
}
