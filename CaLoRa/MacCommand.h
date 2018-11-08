
#ifndef LORA_LORAMACCOMMAND_H
#define LORA_LORAMACCOMMAND_H

#include <stdint.h>
#include <stddef.h>
#include <string.h>

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

/*!
 * LoRaMAC server MAC commands
 *
 * LoRaWAN Specification V1.1.0 chapter 5, table 4
 */
typedef enum eLoRaMacServerCommand {
    /*!
     * ResetInd
     */
            SRV_MAC_RESET_CONF = 0x01,
    /*!
     * LinkCheckAns
     */
            SRV_MAC_LINK_CHECK_ANS = 0x02,
    /*!
     * LinkADRReq
     */
            SRV_MAC_LINK_ADR_REQ = 0x03,
    /*!
     * DutyCycleReq
     */
            SRV_MAC_DUTY_CYCLE_REQ = 0x04,
    /*!
     * RXParamSetupReq
     */
            SRV_MAC_RX_PARAM_SETUP_REQ = 0x05,
    /*!
     * DevStatusReq
     */
            SRV_MAC_DEV_STATUS_REQ = 0x06,
    /*!
     * NewChannelReq
     */
            SRV_MAC_NEW_CHANNEL_REQ = 0x07,
    /*!
     * RXTimingSetupReq
     */
            SRV_MAC_RX_TIMING_SETUP_REQ = 0x08,
    /*!
     * NewChannelReq
     */
            SRV_MAC_TX_PARAM_SETUP_REQ = 0x09,
    /*!
     * DlChannelReq
     */
            SRV_MAC_DL_CHANNEL_REQ = 0x0A,
    /*!
     * DeviceTimeAns
     */
            SRV_MAC_DEVICE_TIME_ANS = 0x0D,
    /*!
     * PingSlotInfoAns
     */
            SRV_MAC_PING_SLOT_INFO_ANS = 0x10,
    /*!
     * PingSlotChannelReq
     */
            SRV_MAC_PING_SLOT_CHANNEL_REQ = 0x11,
    /*!
     * BeaconTimingAns
     */
            SRV_MAC_BEACON_TIMING_ANS = 0x12,
    /*!
     * BeaconFreqReq
     */
            SRV_MAC_BEACON_FREQ_REQ = 0x13,
} LoRaMacServerCommand;

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

    LoRaMacCommandStatus RemoveCommand(MacCommand *macCommand);

    bool InsertToFrame(uint8_t *fOpts, uint8_t *fOptsLen);
};

#endif //LORA_LORAMACCOMMAND_H
