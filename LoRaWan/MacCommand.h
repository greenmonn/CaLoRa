
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
    uint8_t CommandID;
    uint8_t Payload[LORAMAC_COMMADS_MAX_NUM_OF_PARAMS];
    size_t PayloadSize;
};

class MacCommandsList : private List<MacCommand> {
    LoRaMacCommandStatus AddCommand(uint8_t commandID, uint8_t* payload, size_t payloadSize);
    LoRaMacCommandStatus RemoveCommand(MacCommand *macCommand);
};

class MacCommandsContext {
    MacCommandsList macCommandsList;

    size_t serializedCommandsSize;

public:
    bool AddMacCommandsToFrame(uint8_t *payload);
};

/* Add or Remove a mac command to be sent */
LoRaMacCommandStatus MacCommandsList::AddCommand(uint8_t commandID, uint8_t* payload, size_t payloadSize) {

    // increase serializedCommandsSize
    return LORAMAC_COMMANDS_SUCCESS;
}

LoRaMacCommandStatus MacCommandsList::RemoveCommand(MacCommand *macCommand) {

    // decrease serializedCommandsSize
    return LORAMAC_COMMANDS_SUCCESS;
};

/* Creating Mac Commands Payload by Mac Commands List */
bool MacCommandsContext::AddMacCommandsToFrame(uint8_t *payload) {
    // Refer Reference Code: `PrepareFrame` in LoRaMac.c
}

/* Processing Mac Commands */
bool ProcessMacCommands(uint8_t *payload, uint8_t macIndex, uint8_t commandsSize) {
    // Refer Reference Code: `ProcessMacCommands` in LoRaMac.c
}

/* Save or Restore Context */

#endif //LORA_LORAMACCOMMAND_H
