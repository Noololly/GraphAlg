//
// Created by olly on 31/03/2026.
//

#ifndef GRAPHALG_OPQUEUE_H
#define GRAPHALG_OPQUEUE_H
#include "oQueue.h"

template <class T>
class oPQueue : public oQueue<T> {
public:
    explicit oPQueue(int qSize);
    void push(const T& element);

};

template<class T>
oPQueue<T>::oPQueue(const int qSize) : oQueue<T>(qSize) {
    this->size = qSize;
    this->data = new T[qSize];
    this->front = this->data;
    this->rear = this->data;
    this->count = 0;
}

template<class T>
void oPQueue<T>::push(const T &element) {
    int i = this->count - 1;
    while ( i >= 0 && this->data[i] > element) {
        this->data[i+1] = this->data[i];
        --i;
    }
    this->data[i+1] = element;
    ++this->count;
}



#endif //GRAPHALG_OPQUEUE_H
