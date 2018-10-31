
#include "MacCommand.h"

#define CID_FIELD_SIZE  1

/*!
 * LoRaMAC server MAC commands
 *
 * LoRaWAN Specification V1.1.0 chapter 5, table 4
 */
typedef enum eLoRaMacSrvCmd {
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
} LoRaMacSrvCmd;

LoRaMacCommandStatus MacCommandsContext::serialize(size_t availableSize, uint8_t *buffer) {
    List<MacCommand>::iterator iter = this->macCommandsList.Begin();

    uint8_t bytesWrote = 0;

    while (iter != this->macCommandsList.End()) {
        MacCommand *currentCommand = iter.Data();

        if ((availableSize - bytesWrote) >= (CID_FIELD_SIZE + currentCommand->PayloadSize)) {
            buffer[bytesWrote++] = currentCommand->CommandID;
            memcpy(&buffer[bytesWrote], currentCommand->Payload, currentCommand->PayloadSize);

            bytesWrote += currentCommand->PayloadSize;
        } else {
            break;
        }

        iter++;
    }
    return LORAMAC_COMMANDS_SUCCESS;
}

LoRaMacCommandStatus MacCommandsContext::AddCommand(uint8_t commandID, uint8_t *payload, size_t payloadSize) {

    MacCommand newCommand = MacCommand(commandID, payload, payloadSize);

    this->macCommandsList.Add(&newCommand);

    this->serializedCommandsSize += (CID_FIELD_SIZE + payloadSize);

    return LORAMAC_COMMANDS_SUCCESS;
}

LoRaMacCommandStatus MacCommandsContext::RemoveCommand(MacCommand *macCommand) {

    size_t payloadSize = macCommand->PayloadSize;

    this->macCommandsList.Remove(macCommand);

    this->serializedCommandsSize -= (CID_FIELD_SIZE + payloadSize);

    return LORAMAC_COMMANDS_SUCCESS;
};

bool MacCommandsContext::InsertToFrame(
        uint8_t *fOpts,
        size_t *fOptsLen,
        uint8_t *FRMPayload,
        size_t *FRMPayloadSize,
        uint8_t appDataSize,
        uint8_t availableAppPayloadSize) {

    // Refer Reference Code: `PrepareFrame` in LoRaMac.c

    if (this->serializedCommandsSize == 0)
        return false;

    if (appDataSize == 0) {
        this->serialize(availableAppPayloadSize, FRMPayload);
        *FRMPayloadSize = this->serializedCommandsSize;

        return true;
    }

    if (this->serializedCommandsSize <= LORA_MAC_COMMAND_MAX_FOPTS_LENGTH) {
        this->serialize(LORA_MAC_COMMAND_MAX_FOPTS_LENGTH, fOpts);
        *fOptsLen = this->serializedCommandsSize;
    } else {
        // TODO: serialize available commands and skip for exceeding space
    }
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