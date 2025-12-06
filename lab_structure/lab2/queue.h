#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>
#include "stack.h"

template <typename T>
class Queue {
private:
    Stack<T> in;
    Stack<T> out;

    void shift();

public:
    Queue(std::int64_t maxSize = 100);

    bool isEmpty();
    void enqueue(const T& value);
    T dequeue();
    std::int64_t size();
};

extern template class Queue<int>;
extern template class Queue<float>;
extern template class Queue<double>;

#endif // QUEUE_H