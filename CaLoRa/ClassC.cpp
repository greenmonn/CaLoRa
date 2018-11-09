#include "ClassC.h"


void ClassC::oneLoop() {

	uint8_t length;

	switch (radioDriver.mode()) {

		case RHGenericDriver::RHModeSleep:
			break;

		case RHGenericDriver::RHModeIdle:

			// tx -> idle, which means transmission is finished
			if (lorawanStatus == LORAWAN_TX) {
				beginReceiveWindow2();

				// schedule first, second receive window
				timer.schedule(RECEIVE_DELAY1, beginReceiveWindow1);
				timer.schedule(RECEIVE_DELAY2, beginReceiveWindow2);
			}
			break;

		case RHGenericDriver::RHModeTx:
			break;

		case RHGenericDriver::RHModeRx:

			// get received packet
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

	// open receive window for RECEIVE_DURATION
	radioDriver.setModeRx();
	radioDriver.setFrequency(RX1_FREQUENCY);
	lorawanStatus = LORAWAN_RX;
}

void ClassC::beginReceiveWindow2() {

	// open receive window for RECEIVE_DURATION
	radioDriver.setModeRx();
	radioDriver.setFrequency(RX2_FREQUENCY);
	lorawanStatus = LORAWAN_RX;
}



