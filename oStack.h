//
// Created by olly on 30/03/2026.
//

#ifndef DIJKSTRA2_STACK_H
#define DIJKSTRA2_STACK_H

#include <vector>
#include <stdexcept>

template <class T>
class oStack {
public:
    oStack() = default;
    void push(const T& element);
    T pop();
    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] int getSize() const;

private:
    std::vector<T> data;
    int elements{};
};

template <class T>
void oStack<T>::push(const T& element) {
    data.push_back(element);
    ++elements;
}

template<class T>
T oStack<T>::pop() {
    if (data.empty()) {
        throw std::runtime_error("Pop from empty stack");
    }

    T value = data.back();
    data.pop_back();
    --elements;
    return value;
}

template<class T>
bool oStack<T>::isEmpty() const {
    return data.empty();
}

template<class T>
int oStack<T>::getSize() const {
    return elements;
}
#endif //DIJKSTRA2_STACK_H
