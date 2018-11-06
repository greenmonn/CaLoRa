#ifndef LORA_CLASSA_H
#define LORA_CLASSA_H

#include <SPI.h>

#include "SendQueue.h"
#include "Framer.h"
#include "Timer.h"
#include "LoRaWan.h"


/*
 *		CLASS A:
 *
 *                              |<-   DELAY1  ->|
 *                              |<-           DELAY2            ->|
 *
 *    ------------+-------------+---------------+---------+-------+---------+-------
 *                |             |               |         |       |         |
 *                |      TX     |               |   RX1   |       |   RX2   |
 *                |             |               |         |       |         |
 *    ------------+-------------+---------------+---------+-------+---------+-------
 *
 *        sleep   |  transmit   |      idle     | receive | idle  | receive |  sleep
 */

#define RECEIVE_DELAY1				20
#define RECEIVE_DELAY2				100
#define RECEIVE_DURATION			20

class ClassA: public LoRaWan {

private:
		static void beginReceiveWindow1();
		static void endReceiveWindow1();
		static void beginReceiveWindow2();
		static void endReceiveWindow2();

public:
		explicit ClassA(recv_callback_t): LoRaWan(recvCallback) {};
		void oneLoop();

};

#endif //LORA_CLASSA_H
