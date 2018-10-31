
#ifndef LORA_LORAMACCOMMAND_H
#define LORA_LORAMACCOMMAND_H

#include <stdint.h>
#include <stddef.h>

#include "List.h"

#define LORAMAC_COMMADS_MAX_NUM_OF_PARAMS   2

/*
 * MacCommand:
 * 	- provide abstraction on mac command
 */

#define LORA_MAC_COMMAND_MAX_FOPTS_LENGTH           15


typedef enum enumLoRaMacCommandsStatus {
    /*!
     * No error occurred
     */
            LORAMAC_COMMANDS_SUCCESS = 0,
    /*!
     * Null pointer exception
     */
            LORAMAC_COMMANDS_ERROR_NULL_POINTER,
    /*!
     * There is no memory left to add a further MAC command
     */
            LORAMAC_COMMANDS_ERROR_MEMORY,
    /*!
     * MAC command not found.
     */
            LORAMAC_COMMANDS_ERROR_CMD_NOT_FOUND,
    /*!
     * Unknown or corrupted command error occurred.
     */
            LORAMAC_COMMANDS_ERROR_UNKNOWN_CMD,
    /*!
     * Undefined Error occurred
     */
            LORAMAC_COMMANDS_ERROR_UNDEFINED,
} LoRaMacCommandStatus;

class MacCommand {
public:
    MacCommand(uint8_t commandID, uint8_t *payload, size_t payloadSize) {
        this->CommandID = commandID;
        this->PayloadSize = payloadSize;
        memcpy(this->Payload, payload, payloadSize);
    }

    bool operator==(const MacCommand& macCommand) {
        return (this->CommandID == macCommand.CommandID
        && this->Payload == macCommand.Payload
        && this->PayloadSize == macCommand.PayloadSize);
    }

    uint8_t CommandID;
    uint8_t Payload[LORAMAC_COMMADS_MAX_NUM_OF_PARAMS];
    size_t PayloadSize;
};

class MacCommandsContext {
    List<MacCommand> macCommandsList;

    size_t serializedCommandsSize;

    LoRaMacCommandStatus serialize(size_t availableSize, uint8_t *buffer);


public:
    LoRaMacCommandStatus AddCommand(uint8_t commandID, uint8_t *payload, size_t payloadSize);

    LoRaMacCommandStatus RemoveCommand(MacCommand *macCommand);

    bool InsertToFrame(
            uint8_t *fOpts,
            size_t *fOptsLen,
            uint8_t *FRMPayload,
            size_t *FRMPayloadSize,
            uint8_t appDataSize,
            uint8_t availableAppPayloadSize);
};

#endif //LORA_LORAMACCOMMAND_H
