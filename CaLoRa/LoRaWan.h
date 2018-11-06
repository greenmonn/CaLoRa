#ifndef LORA_LORAMAC_H
#define LORA_LORAMAC_H

#include "RH_RF95.h"
#include "SendQueue.h"
#include "Framer.h"
#include "Timer.h"


typedef void(*recv_callback_t)(uint8_t *, int);

/*
 * LoRaWan:
 * 	- LoRaWan layer implementation
 */

#define FREQUENCY              868.0
#define MAX_PHY_PAYLOAD        247

typedef RH_RF95 RadioDriver;
typedef enum {LORAWAN_TX, LORAWAN_RX, LORAWAN_IDLE, LORAWAN_SLEEP} lorawan_status_t;

class LoRaWan {

protected:

		/* LoRaWan dependencies */
		static RadioDriver radioDriver;			// radio driver
		static Framer framer;
		static SendQueue sendQueue;
		static Timer timer;

		/* LoRaWan packet buffer, receive callback */
		static uint8_t packetBuffer[MAX_PHY_PAYLOAD];
		static recv_callback_t recvCallback;

		/* LoRaWan Status */
		static lorawan_status_t lorawanStatus;

		int getNextDataRate() { return 0; }                          // ADR(adaptive data rate). get next data rate from existing radio state

public:

		explicit LoRaWan(recv_callback_t recvCallback);

		/* application interface */
		bool init();
		bool send(uint8_t *packet, uint8_t length);
		void updateTimer();

		virtual void oneLoop() = 0;
};

#endif //LORA_LORAMAC_H
