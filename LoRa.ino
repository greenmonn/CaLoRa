#include "LoRaWan.h"

#define SERIAL_BAUDRATE 9600

LoRaWan* loRaWan;

void recv_callback(uint8_t* message, int length){
	Serial.println((char*)message);
}

void setup()
{
	// Wait for serial port to be available
	Serial.begin(SERIAL_BAUDRATE);
	while (!Serial) ;
	Serial.println("Start Sketch");

	// initialize lora wan
	loRaWan = LoRaWan::getInstance();
	if(!loRaWan->init(recv_callback)) {
		Serial.println("LoRa init failed");
		exit(0);
	}
}

/*
 * application loop
 * -
 */
void loop()
{
	/* application codes
	 * 	- delay() function should not be used in main loop
	 *
	 * ex)
	 * 	haveSomethingToSend = getSensorData();
	 * 	if (haveSomethingToSend)
	 * 		LoRaWan::requestSend((uint8_t*)"test", sizeof("test"));
	 */

	// LoRa loop
	loRaWan->oneLoop();
}