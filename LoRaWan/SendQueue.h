#ifndef LORA_SENDQUEUE_H
#define LORA_SENDQUEUE_H

#include <stdint.h>
#include "List.h"

/*
 * SendQueue:
 * 	- Queue for messages from app layer
 */

class SendQueue {

private:
    class Message {
    public:
        uint8_t length;
        uint8_t *data;

        Message(uint8_t *_data, uint8_t _length) {
            length = _length;
            data = _data;
        }

        bool operator==(const Message &message) const {
            return (data == message.data) && (length == message.length);
        }
    };

    List<Message> queue;

public:
    bool push(uint8_t *message, uint8_t length);

    bool pop(uint8_t *message, uint8_t *length);

    int length();
};


#endif //LORA_SENDQUEUE_H
