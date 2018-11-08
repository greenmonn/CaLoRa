#ifndef LORA_CLASSC_H
#define LORA_CLASSC_H

#include <SPI.h>

#include "SendQueue.h"
#include "Framer.h"
#include "Timer.h"
#include "LoRaWan.h"


/*
 *		CLASS C:
 *
 *                              |<-   DELAY1  ->|
 *                              |<-           DELAY2            ->|
 *
 *    ------------+-------------+---------------+---------+-------+-------------------------
 *                |             |               |         |       |
 *         RX2    |      TX     |               |   RX1   |       |           RX2
 *                |             |               |         |       |
 *    ------------+-------------+---------------+---------+-------+-------------------------
 *
 *       receive  |  transmit   |      idle     | receive | idle  |  receive (continuously)
 */

#define RECEIVE_DELAY1				20
#define RECEIVE_DELAY2				100
#define RECEIVE_DURATION			20

class ClassC: public LoRaWan {

private:
		static void beginReceiveWindow1();
		static void endReceiveWindow1();
		static void beginReceiveWindow2();
		static void endReceiveWindow2();

public:
		explicit ClassC(recv_callback_t): LoRaWan(recvCallback) {};
		void oneLoop();

};

#endif //LORA_CLASSC_H
