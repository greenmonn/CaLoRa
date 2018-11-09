
#include "MacCommand.h"

const size_t MacCommandsContext::GetSerializedCommandsSize() {
    return this->serializedCommandsSize;
}

LoRaMacCommandStatus MacCommandsContext::serialize(uint8_t availableSize, uint8_t *buffer) {
    List<MacCommand>::Iterator iter = this->macCommandsList.Begin();

    uint8_t bytesWrote = 0;

    while (iter != this->macCommandsList.End()) {
        MacCommand currentCommand = *iter;

        if ((availableSize - bytesWrote) >= (CID_FIELD_SIZE + currentCommand.PayloadSize)) {
            buffer[bytesWrote++] = currentCommand.CommandID;
            memcpy(&buffer[bytesWrote], currentCommand.Payload, currentCommand.PayloadSize);

            bytesWrote += currentCommand.PayloadSize;

            iter = this->macCommandsList.Erase(iter);
            this->serializedCommandsSize -= (CID_FIELD_SIZE + currentCommand.PayloadSize);
        } else {
            break;
        }
    }
    return LORAMAC_COMMANDS_SUCCESS;
}

LoRaMacCommandStatus MacCommandsContext::AddCommand(uint8_t commandID, uint8_t *payload, uint8_t payloadSize) {

    MacCommand newCommand = MacCommand(commandID, payload, payloadSize);

    List<MacCommand>::Iterator iter = this->macCommandsList.End();
    this->macCommandsList.Insert(iter, newCommand);

    this->serializedCommandsSize += (CID_FIELD_SIZE + payloadSize);

    return LORAMAC_COMMANDS_SUCCESS;
}

bool MacCommandsContext::InsertToFrame(
        uint8_t *fOpts,
        uint8_t *fOptsLen) {

    if (this->serializedCommandsSize == 0) {
        *fOptsLen = 0;
        return false;
    }

    *fOptsLen = this->serializedCommandsSize;
    this->serialize(LORA_MAC_COMMAND_MAX_FOPTS_LENGTH, fOpts);

    return true;
}

/* TODO: Processing Mac Commands */
bool ProcessMacCommands(uint8_t *payload, uint8_t macIndex, uint8_t commandsSize) {

    // Refer Reference Code: `ProcessMacCommands` in LoRaMac.c
    while (macIndex < commandsSize) {
        switch (payload[macIndex++]) {
            case MAC_LINK_CHECK_REQ:
            case MAC_LINK_CHECK_ANS:
            case MAC_DEV_STATUS_REQ:
            case MAC_DEV_STATUS_ANS:
                break;
            default:
                return false;
        }
    }

    return true;
}