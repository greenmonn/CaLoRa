#include <string.h>

#include "SendQueue.h"

bool SendQueue::push(uint8_t *data, uint8_t length) {
    Message message = Message(data, length);

    this->queue.Add(&message);

    return true;
}

bool SendQueue::pop(uint8_t *data, uint8_t *length) {
    Message *message = this->queue.GetFirst();

    memcpy(data, message->data, message->length);
    *length = message->length;

    this->queue.Remove(message);

    return true;
}

int SendQueue::length() {
    return this->queue.Length();
}
