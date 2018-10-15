#include <LoRaWan/LoRaWan.h>
#include <time.h>

#define SERIAL_BAUDRATE 9600
#define RF_FREQUENCY 868.0

void recv_callback(uint8_t* message, int length){
	Serial.println((char*)message);
}

void setup()
{
	Serial.begin(SERIAL_BAUDRATE);

	while (!Serial) ; // Wait for serial port to be available
	Serial.println("Start Sketch");

	LoRaWan::init(RF_FREQUENCY);
	LoRaWan::setRecvCallback(recv_callback);
}

/*
 * application loop
 * -
 */
void loop()
{
	char payload[] = "test string";
	bool haveSomethingToSend = true;

	/* application stuff */
	// haveSomethingToSend = getSensorData();

	if (haveSomethingToSend)
		LoRaWan::requestSend((uint8_t*)payload, sizeof(payload));



	// LoRa loop
	LoRaWan::oneLoop();
}