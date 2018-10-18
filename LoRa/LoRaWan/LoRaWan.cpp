#include "LoRaWan.h"

RH_RF95 LoRaWan::rf95;
LoRaClass LoRaWan::currentClass;
SendQueue LoRaWan::sendQueue;

LoRaWan::LoRaWan() {
}

LoRaClass LoRaWan::getCurrentClass() {
	return currentClass;
}

void LoRaWan::changeClass(LoRaClass) {
}

bool LoRaWan::init(float frequency) {

	if (!rf95.init())
		return false;

	rf95.setFrequency(frequency);
	rf95.setTxPower(13);
	rf95.setSpreadingFactor(7);
	rf95.setSignalBandwidth(125000);
	rf95.setCodingRate4(5);

	return true;
}

bool LoRaWan::setRecvCallback(recv_callback_t recv_callback) {
	return false;
}

bool LoRaWan::requestSend(uint8_t* pPayload, int length) {
	return sendQueue.push(pPayload, length);
}

void LoRaWan::oneLoop() {

	// on receiving packet
	// 	process packet
//	LoRaWan::recv_callback((uint8_t *) "message contents", 20);

//	if (rf95.available())
//	{
//		// Should be a message for us now
//		uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
//		uint8_t len = sizeof(buf);
//		if (rf95.recv(buf, &len))
//		{
//			RH_RF95::printBuffer("request: ", buf, len);
//			Serial.print("got request: ");
//			Serial.println((char*)buf);
//			Serial.print("RSSI: ");
//			Serial.println(rf95.lastRssi(), DEC);
//
//			// Send a reply
//			uint8_t data[] = "And hello back to you";
//			rf95.send(data, sizeof(data));
//			rf95.waitPacketSent();
//			Serial.println("Sent a reply");
//			digitalWrite(led, LOW);
//		}
//		else
//		{
//			Serial.println("recv failed");
//		}
//	}
}

int LoRaWan::getNextDataRate() {
	return 0;
}