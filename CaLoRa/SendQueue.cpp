#include <string.h>

#include "SendQueue.h"

bool SendQueue::push(uint8_t *data, uint8_t length) {
    Message message = Message(data, length);

    List<Message>::Iterator iter = this->queue.End();

    this->queue.Insert(iter, message);

    return true;
}

bool SendQueue::pop(uint8_t *data, uint8_t *length) {
    List<Message>::Iterator iter = this->queue.Begin();

    Message message = *iter;

    memcpy(data, message.data, message.length);
    *length = message.length;

    this->queue.Erase(iter);

    return true;
}

int SendQueue::length() {
    return this->queue.Length();
}
