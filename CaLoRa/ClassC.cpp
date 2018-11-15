#include "ClassC.h"


void ClassC::oneLoop() {

	uint8_t length;

	switch (radioDriver.mode()) {

		case RHGenericDriver::RHModeSleep:
			break;

		case RHGenericDriver::RHModeIdle:
			if (lorawanStatus == LORAWAN_TX) {
				beginReceiveWindow2();

				timer.schedule(RECEIVE_DELAY1, beginReceiveWindow1);
			}
			break;

		case RHGenericDriver::RHModeTx:
			break;

		case RHGenericDriver::RHModeRx:
			if (radioDriver.available()) {
				if (radioDriver.recv(packetBuffer, &length)) {

					// TODO: process received header
					// loRaHeader = framer.parse(packetBuffer, &length);

					recvCallback(packetBuffer, length);
				}
			}

			// check if there are messages from upper(app) layer
			if (sendQueue.pop(packetBuffer, &length)) {
				// TODO: properly set lora header
				// framer.create(packetBuffer, &length, loRaHeader);
				radioDriver.send(packetBuffer, length);
				lorawanStatus = LORAWAN_TX;
			}

			break;

			/* unused radio modes */
		case RHGenericDriver::RHModeInitialising:
			break;
		case RHGenericDriver::RHModeCad:
			break;
	}
}

void ClassC::beginReceiveWindow1() {
	radioDriver.setModeRx();

	// TODO: set RX1 frequency as a function of uplink frequency
	radioDriver.setFrequency(RX1_FREQUENCY);
	lorawanStatus = LORAWAN_RX;

	timer.schedule(RECEIVE_DURATION, beginReceiveWindow2);
}

void ClassC::beginReceiveWindow2() {
	radioDriver.setModeRx();
	radioDriver.setFrequency(RX2_FREQUENCY);
	lorawanStatus = LORAWAN_RX;
}



