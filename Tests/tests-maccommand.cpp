#include <stdint.h>
#include "catch.hpp"

#include "MacCommand.h"

TEST_CASE("Add mac command to current context", "[MacCommand]") {
    MacCommandsContext currentContext = MacCommandsContext();

    REQUIRE(currentContext.GetSerializedCommandsSize() == 0);

    LoRaMacCommand commandID = MAC_LINK_CHECK_REQ;
    uint8_t macCommandPayload[2] = { 0x00, 0x00 };
    uint8_t payloadSize = 2;

    LoRaMacCommandStatus status = currentContext.AddCommand(commandID, macCommandPayload, payloadSize);

    REQUIRE(status == LORAMAC_COMMANDS_SUCCESS);

    REQUIRE(currentContext.GetSerializedCommandsSize() == CID_FIELD_SIZE + payloadSize);
}

TEST_CASE("Serialize mac commands in the list to insert frame", "[MacCommand]") {
    MacCommandsContext currentContext = MacCommandsContext();

    LoRaMacCommand commandID = MAC_LINK_CHECK_REQ;
    uint8_t macCommandPayload[2] = { 0x00, 0x00 };
    uint8_t payloadSize = 2;

    LoRaMacCommand commandID2 = MAC_DEV_STATUS_REQ;
    uint8_t macCommandPayload2[2] = { 0x00 };
    uint8_t payloadSize2 = 1;

    currentContext.AddCommand(commandID, macCommandPayload, payloadSize);
    currentContext.AddCommand(commandID2, macCommandPayload2, payloadSize2);

    uint8_t *fOptsField = (uint8_t *)malloc(LORA_MAC_COMMAND_MAX_FOPTS_LENGTH);
    uint8_t size;

    currentContext.InsertToFrame(fOptsField, &size);

    REQUIRE(fOptsField[0] == MAC_LINK_CHECK_REQ);
    REQUIRE(fOptsField[3] == MAC_DEV_STATUS_REQ);
    REQUIRE(size == 5);
}