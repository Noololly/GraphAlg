//
// Created by olly on 30/03/2026.
//

#ifndef GRAPHALG_OQUEUE_H
#define GRAPHALG_OQUEUE_H
#include <stdexcept>

template<class T>
class oQueue {
public:
    explicit oQueue(int size);
    ~oQueue();
    void push(const T& element);
    T pop();
    [[nodiscard]] bool isEmpty() const;
protected:
    T* front;
    T* rear;
    int size;
    T* data;
    int count;
};


template<class T>
oQueue<T>::oQueue(const int size) {
    this->size = size;
    this->data = new T[size];
    front = &data[0];
    rear = &data[0];
    count = 0;
}

template<class T>
oQueue<T>::~oQueue() {
    delete [] data; // no memory leaks tyvm
}

template<class T>
void oQueue<T>::push(const T &element) {
    *rear = element;
    ++rear;
    if (rear == data + size) {
        rear = data;
    }
    ++count;
}

template<class T>
T oQueue<T>::pop() {
    if (this->isEmpty()) {
        throw std::runtime_error("Pop from empty queue");
    }
    T element = *front;
    ++front;
    --count;
    return element;
}

template<class T>
bool oQueue<T>::isEmpty() const {
    return count == 0;
}

#endif //GRAPHALG_OQUEUE_H
