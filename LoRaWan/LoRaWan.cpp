#include "LoRaWan.h"

LoRaWan* LoRaWan::instance;

LoRaWan::LoRaWan() : sendQueue(), packetBuffer(), length() {
	transmitting = false;
}

LoRaClass LoRaWan::getCurrentClass() {
	return currentClass;
}

void LoRaWan::changeClass(LoRaClass loRaClass) {
	currentClass = loRaClass;
}

bool LoRaWan::init(recv_callback_t recvCallback) {

	if (!radioDriver.init())
		return false;

	radioDriver.setFrequency(FREQUENCY);
	radioDriver.setTxPower(13);
	radioDriver.setSpreadingFactor(7);
	radioDriver.setSignalBandwidth(125000);
	radioDriver.setCodingRate4(5);
	this->recvCallback = recvCallback;
	return true;
}

bool LoRaWan::requestSend(uint8_t *pPayload, uint8_t length) {
	return sendQueue.push(pPayload, length);
}

void LoRaWan::oneLoop() {

	switch (radioDriver.mode()) {

		// in case radio in sleep
		case RHGenericDriver::RHModeSleep:

			// check if there are messages from upper(app) layer
			if (sendQueue.pop(packetBuffer, &length)) {

				// TODO: properly set lora header

				framer.create(packetBuffer, &MHDR,&FHDR,&FPort,&length);
				radioDriver.send(packetBuffer, length);
				transmitting = true;
			}
			break;

		// in case radio receiving (receive window opened)
		case RHGenericDriver::RHModeRx:

			// get received packet
			if (radioDriver.available()) {
				if (radioDriver.recv(packetBuffer, &length)) {

					framer.parse(packetBuffer,&MHDR,&FHDR,&FPort,FRMPayLoad,&length);//return FRMlength
					// TODO: process received header
					recvCallback(packetBuffer, length);
				}
			}
			break;

		// in case radio idle
		case RHGenericDriver::RHModeIdle:

			// tx -> idle, which means transmission is finished
			if (transmitting) {

				transmitting = false;

				// schedule first, second receive window
				timer.schedule(RECEIVE_DELAY1, beginReceiveWindow1);
				timer.schedule(RECEIVE_DELAY2, beginReceiveWindow2);
			}

			break;

		// in case radio transmitting, keep transmit
		case RHGenericDriver::RHModeTx: break;

		// unused cases
		case RHGenericDriver::RHModeInitialising: break;
		case RHGenericDriver::RHModeCad: break;
	}

	timer.update();
}

void LoRaWan::beginReceiveWindow1() {
	// open receive window for RECEIVE_DURATION
	instance->radioDriver.setModeRx();
	instance->timer.schedule(RECEIVE_DURATION, endReceiveWindow1);
}

void LoRaWan::endReceiveWindow1() {
	// close receive window go to idle
	instance->radioDriver.setModeIdle();
}

void LoRaWan::beginReceiveWindow2() {
	// open receive window for RECEIVE_DURATION
	instance->radioDriver.setModeRx();
	instance->timer.schedule(RECEIVE_DURATION, endReceiveWindow2);
}

void LoRaWan::endReceiveWindow2() {
	// close receive window go to sleep
	instance->radioDriver.sleep();
}

int LoRaWan::getNextDataRate() {
	return 0;
}