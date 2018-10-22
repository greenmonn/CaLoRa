#ifndef LORA_SENDQUEUE_H
#define LORA_SENDQUEUE_H

#include <stdint.h>


/*
 * SendQueue:
 * 	- Queue for messages from app layer
 */

class SendQueue {

private:
		typedef struct _Elem{
				uint8_t * message;
				struct _Elem* next;
		} Elem;

		Elem* head;
		int len;

public:

		bool push(uint8_t *message, uint8_t length);			// push app message to queue
		bool pop(uint8_t *message, uint8_t *length);			// pop next app message
		int length();
};


#endif //LORA_SENDQUEUE_H
