#ifndef LORA_LORAMAC_H
#define LORA_LORAMAC_H

#include <SPI.h>

#include "RH_RF95.h"
#include "LoRaClass.h"
#include "SendQueue.h"
#include "Framer.h"
#include "Timer.h"


/*
 * LoRaWan:
 * 	- LoRaWan(mac layer) singleton implementation
 */

#define FREQUENCY							868.0
#define MAX_PHY_PAYLOAD 			247


/*
 *		CLASS A:
 */
#define RECEIVE_DELAY1				20
#define RECEIVE_DELAY2				100
#define RECEIVE_DURATION			20
/*
 *
 * 															|<- 	DELAY1	->|
 *															|<-						DELAY2						->|
 *
 *		------------+-------------+---------------+---------+-------+---------+-------
 *								|							|								|				  |				|					|
 *								|			TX			|								|   RX 1 	|				|		RX2		|
 *								|							|								|					|				|					|
 *		------------+-------------+---------------+---------+-------+---------+-------
 *
 *		 		sleep		|	 	transmit 	|  		 idle 		|	receive	|	 idle	| receive	|  sleep
 */


class LoRaWan {

private:

		/* internal typedefs */
		typedef RH_RF95 RadioDriver;
		typedef void(*recv_callback_t)(uint8_t*, int);

		/* LoRaWan dependencies */
		RadioDriver radioDriver;												// radio driver
		LoRaClass currentClass;													// current lora class - not used for now
		SendQueue sendQueue;
		Framer framer;
		Timer timer;

		/* LoRaWan packet variables */
		uint8_t packetBuffer[MAX_PHY_PAYLOAD];
		uint8_t length;
		LoRaHeader loRaHeader;

		/* LoRaWan state variable */
		bool transmitting;

		/* callbacks */
		recv_callback_t recvCallback;

		/* LoRaWan internal methods */
		static void beginReceiveWindow1();
		static void endReceiveWindow1();
		static void beginReceiveWindow2();
		static void endReceiveWindow2();

		int getNextDataRate();													// ADR(adaptive data rate). get next data rate from existing radio state

public:

		/* class related interface */
		LoRaClass getCurrentClass();
		void changeClass(LoRaClass);

		/* application interface */
		bool init(recv_callback_t recvCallback);
		bool requestSend(uint8_t *, uint8_t);
		void oneLoop();


		/* singleton pattern */
private:
		LoRaWan();
		static LoRaWan* instance;
public:
		static LoRaWan* getInstance()
		{
			if (!instance)
				instance = new LoRaWan();
			return instance;
		}
};

#endif //LORA_LORAMAC_H
