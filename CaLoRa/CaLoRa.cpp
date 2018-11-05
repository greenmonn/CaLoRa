#include "CaLoRa.h"

CaLoRa::CaLoRa(recv_callback_t recvCallback) {
	this->recvCallback = recvCallback;
	this->loRaWan = new ClassA(this->recvCallback);
}

bool CaLoRa::init() {
	return !this->loRaWan->init();
}

void CaLoRa::oneLoop() {
	loRaWan->oneLoop();
	loRaWan->updateTimer();
}

void CaLoRa::send(uint8_t *packet, uint8_t length) {
	loRaWan->send(packet, length);
}

