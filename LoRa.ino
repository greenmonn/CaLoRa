#include <stdint.h>
#include "Arduino.h"
#include "CaLoRa.h"

#define SERIAL_BAUDRATE 9600

CaLoRa *caLoRa;

void recv_callback(uint8_t* message, int length){
	Serial.println((char*)message);
}

void setup()
{
	// Wait for serial port to be available
	Serial.begin(SERIAL_BAUDRATE);
	while (!Serial) ;
	Serial.println("Serial started");

	// initialize CaLoRa
	caLoRa = new CaLoRa(recv_callback);
	if(!caLoRa->init()) {
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
	 * 	  caLoRa->send((uint8_t*)"test", sizeof("test"));
	 */

	// LoRa loop
	caLoRa->oneLoop();
}