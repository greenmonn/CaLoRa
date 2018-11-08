
#include "MacCommand.h"

#define CID_FIELD_SIZE  1

LoRaMacCommandStatus MacCommandsContext::serialize(uint8_t availableSize, uint8_t *buffer) {
    List<MacCommand>::Iterator iter = this->macCommandsList.Begin();

    uint8_t bytesWrote = 0;

    while (iter != this->macCommandsList.End()) {
        MacCommand currentCommand = *iter;

        if ((availableSize - bytesWrote) >= (CID_FIELD_SIZE + currentCommand.PayloadSize)) {
            buffer[bytesWrote++] = currentCommand.CommandID;
            memcpy(&buffer[bytesWrote], currentCommand.Payload, currentCommand.PayloadSize);

            bytesWrote += currentCommand.PayloadSize;

            RemoveCommand()
        } else {
            break;
        }

        iter++;
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

LoRaMacCommandStatus MacCommandsContext::RemoveCommand(MacCommand *macCommand) {

    uint8_t payloadSize = macCommand->PayloadSize;

    List<MacCommand>::Iterator iter = this->macCommandsList.Begin();

    while (iter != this->macCommandsList.End()) {
        if (*iter == *macCommand) {
            iter = this->macCommandsList.Erase(iter);
        } else {
            iter++;
        }
    }

    this->serializedCommandsSize -= (CID_FIELD_SIZE + payloadSize);

    return LORAMAC_COMMANDS_SUCCESS;
};

bool MacCommandsContext::InsertToFrame(
        uint8_t *fOpts,
        uint8_t *fOptsLen) {
    // Refer Reference Code: `PrepareFrame` in LoRaMac.c

    if (this->serializedCommandsSize == 0) {
        *fOptsLen = 0;
        return false;
    }

    this->serialize(LORA_MAC_COMMAND_MAX_FOPTS_LENGTH, fOpts);

    if (this->serializedCommandsSize <= LORA_MAC_COMMAND_MAX_FOPTS_LENGTH) {
        *fOptsLen = this->serializedCommandsSize;
    } else {
        *fOptsLen = LORA_MAC_COMMAND_MAX_FOPTS_LENGTH;
    }

    return true;
}

/* TODO: Processing Mac Commands */
bool ProcessMacCommands(uint8_t *payload, uint8_t macIndex, uint8_t commandsSize) {

    // Refer Reference Code: `ProcessMacCommands` in LoRaMac.c
    while (macIndex < commandsSize) {
        switch (payload[macIndex++]) {
            case SRV_MAC_LINK_CHECK_ANS:
            case SRV_MAC_LINK_ADR_REQ:
            case SRV_MAC_DUTY_CYCLE_REQ:
            case SRV_MAC_RX_PARAM_SETUP_REQ:
            case SRV_MAC_DEV_STATUS_REQ:
            case SRV_MAC_NEW_CHANNEL_REQ:
            case SRV_MAC_RX_TIMING_SETUP_REQ:
            case SRV_MAC_TX_PARAM_SETUP_REQ:
            case SRV_MAC_DL_CHANNEL_REQ:
                break;
            default:
                return false;
        }
    }

    return true;
}