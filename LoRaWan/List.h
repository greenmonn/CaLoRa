#ifndef LORA_LIST_H
#define LORA_LIST_H

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

template<class T>
class List {
private:
    int length;

    typedef struct _Item {
        T data;
        struct _Item *prev;
        struct _Item *next;

        _Item(const T &_data) : prev(NULL), next(NULL), data(_data) {
        }
    } Item;

    Item *first;

    Item *last;

    Item *removeItem(Item *item);

    Item *insertItem(T& data, Item *pos);

public:
    List();

    int Length();

    class Iterator {
        friend class List;
    private:
        Item *item;
    public:

        Iterator(Item *_item) {
            this->item = _item;
        }

        Iterator operator++() {
            this->item = this->item->next;

            return *this;
        }

        Iterator operator++(int) {
            this->item = this->item->next;

            return *this;
        }

        bool operator==(const Iterator &iter) const {
            return (item == iter.item);
        }

        bool operator!=(const Iterator &iter) const {
            return (item != iter.item);
        }

        T& operator*() {
            return this->item->data;
        }
    };

    Iterator Begin();

    Iterator End();

    Iterator Erase(const Iterator &iter);

    Iterator Insert(const Iterator &iter, T &data);
};

template<class T>
typename List<T>::Iterator List<T>::Begin() {
    return Iterator(first);
}

template<class T>
typename List<T>::Iterator List<T>::End() {
    return Iterator(NULL);
}

template<class T>
typename List<T>::Iterator List<T>::Erase(const List<T>::Iterator &iter) {
    return Iterator(removeItem(iter.item));
}

template<class T>
typename List<T>::Iterator List<T>::Insert(const List<T>::Iterator &iter, T& data) {
    return Iterator(insertItem(data, iter.item));
}

template<class T>
List<T>::List() {
    this->first = NULL;
    this->last = NULL;
    this->length = 0;
}

template<class T>
int List<T>::Length() {
    return this->length;
}

template<class T>
typename List<T>::Item *List<T>::removeItem(Item *item) {
    List<T>::Item *nextItem = item->next;

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

    return nextItem;
}

template<class T>
typename List<T>::Item *List<T>::insertItem(T& data, Item *pos) {
    Item *newItem = new Item(data);

    Item *prevPos;

    if (pos == NULL) {
        prevPos = this->last;
        this->last = newItem;
    } else {
        prevPos = pos->prev;
        pos->prev = newItem;
    }

    newItem->next = pos;
    newItem->prev = prevPos;

    if (prevPos == NULL) {
        this->first = newItem;
    } else {
        prevPos->next = newItem;
    }

    this->length++;

    return newItem;
}


#endif //LORA_LIST_H
