#ifndef LORA_LIST_H
#define LORA_LIST_H

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

using namespace std;

template <class T>
class List {
private:
    typedef struct _Item {
        T *data;
        struct _Item *prev;
        struct _Item *next;

        _Item(T *_data) : prev(NULL), next(NULL) {
            data = (T*)malloc(sizeof(T));
            memcpy(data, _data, sizeof(T));
        }

    } Item;

    int length;

    Item *first;

    Item *last;

    Item *find(T *data);

public:
    List();

    int Length();

    void Add(T *data);

    void Remove(T *data);

    T *GetFirst();

    T *GetLast();
};


template <class T>
List<T>::List() {
    this->first = NULL;
    this->last = NULL;
    this->length = 0;
}

template <class T>
T *List<T>::GetFirst() {
    if (this->first == NULL) {
        return NULL;
    }

    return this->first->data;
}

template <class T>
T *List<T>::GetLast() {
    if (this->first == NULL) {
        return NULL;
    }

    return this->last->data;
}

template <class T>
int List<T>::Length() {
    return this->length;
}

template <class T>
void List<T>::Add(T *data) {
    Item *newItem = (Item *) malloc(sizeof(Item));
    *newItem = Item(data);

    if (this->last == NULL) {
        this->first = newItem;
        this->last = newItem;

        this->length++;

        return;
    }

    newItem->prev = this->last;
    this->last->next = newItem;
    this->last = newItem;

    this->length++;
}

template <class T>
void List<T>::Remove(T *data) {
    Item *item = this->find(data);

    if (item->prev == NULL) {
        this->first = item->next;
    } else {
        item->prev->next = item->next;
    }

    if (item->next == NULL) {
        this->last = item->prev;
    } else {
        item->next->prev = item->prev;

    }

    delete item;

    this->length--;
}

template <class T>
typename List<T>::Item *List<T>::find(T *data) {
    Item *item = this->first;

    while (item != NULL) {
        if (*(item->data) == *data) {
            return item;
        }

        item = item->next;
    }

    return NULL;
}

#endif //LORA_LIST_H
