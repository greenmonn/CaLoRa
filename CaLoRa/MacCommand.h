
#ifndef LORA_LORAMACCOMMAND_H
#define LORA_LORAMACCOMMAND_H

#include <stdint.h>
#include <stddef.h>
#include <string.h>

#include "List.h"

#define CID_FIELD_SIZE  1

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

/*!
 * LoRaMAC server MAC commands
 *
 * LoRaWAN Specification V1.1.0 chapter 5, table 4
 */
typedef enum eLoRaMacCommand {
    /*!
     * LinkCheckReq
     */
            MAC_LINK_CHECK_REQ = 0x01,
    /*!
     * LinkCheckAns
     */
            MAC_LINK_CHECK_ANS = 0x02,
    /*!
     * DevStatusReq
     */
            MAC_DEV_STATUS_REQ = 0x03,
    /*!
    * DevStatusAns
    */
            MAC_DEV_STATUS_ANS = 0x04,

} LoRaMacCommand;

class MacCommand {
public:
    MacCommand(uint8_t commandID, uint8_t *payload, uint8_t payloadSize) {
        this->CommandID = commandID;
        this->PayloadSize = payloadSize;
        memcpy(this->Payload, payload, payloadSize);
    }

    bool operator==(const MacCommand &macCommand) {
        return (this->CommandID == macCommand.CommandID
                && this->Payload == macCommand.Payload
                && this->PayloadSize == macCommand.PayloadSize);
    }

    uint8_t CommandID;
    uint8_t Payload[LORAMAC_COMMADS_MAX_NUM_OF_PARAMS];
    uint8_t PayloadSize;
};

class MacCommandsContext {
    List<MacCommand> macCommandsList;

    uint8_t serializedCommandsSize;

    LoRaMacCommandStatus serialize(uint8_t availableSize, uint8_t *buffer);


public:
    MacCommandsContext():serializedCommandsSize(0){};

    LoRaMacCommandStatus AddCommand(uint8_t commandID, uint8_t *payload, uint8_t payloadSize);

    const size_t GetSerializedCommandsSize();

    LoRaMacCommandStatus AddCommand(uint8_t commandID, uint8_t *payload, size_t payloadSize);

    bool InsertToFrame(uint8_t *fOpts, uint8_t *fOptsLen);
};

#endif //LORA_LORAMACCOMMAND_H
