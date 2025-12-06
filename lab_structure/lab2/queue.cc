#include "queue.h"

template <typename T>
Queue<T>::Queue(std::int64_t maxSize)
    : in(maxSize), out(maxSize) {}

template <typename T>
bool Queue<T>::isEmpty() {
    return in.isEmpty() && out.isEmpty();
}

template <typename T>
void Queue<T>::shift() {
    while (!in.isEmpty()) {
        out.push(in.pop());
    }
}

template <typename T>
void Queue<T>::enqueue(const T& value) {
    in.push(value);
}

template <typename T>
T Queue<T>::dequeue() {
    if (isEmpty())
        throw std::runtime_error("Queue is empty");

    if (out.isEmpty())
        shift();

    return out.pop();
}

template <typename T>
std::int64_t Queue<T>::size() {
    return in.size() + out.size();
}

template class Queue<int>;
template class Queue<float>;
template class Queue<double>;