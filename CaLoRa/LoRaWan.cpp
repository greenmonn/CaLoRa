#include "LoRaWan.h"

/* LoRaWan static members */
RadioDriver LoRaWan::radioDriver;
Framer LoRaWan::framer;
SendQueue LoRaWan::sendQueue;
Timer LoRaWan::timer;
uint8_t LoRaWan::packetBuffer[MAX_PHY_PAYLOAD];
recv_callback_t LoRaWan::recvCallback;
lorawan_status_t LoRaWan::lorawanStatus;

LoRaWan::LoRaWan(recv_callback_t recv) {
	recvCallback = recv;
}

bool LoRaWan::init() {

	if (!radioDriver.init()) return false;

	radioDriver.setFrequency(FREQUENCY);
	radioDriver.setTxPower(13);
	radioDriver.setSpreadingFactor(7);
	radioDriver.setSignalBandwidth(125000);
	radioDriver.setCodingRate4(5);

	return true;
}

bool LoRaWan::send(uint8_t *packet, uint8_t length) {
	return sendQueue.push(packet, length);
}

void LoRaWan::updateTimer() {
	timer.update();
}
