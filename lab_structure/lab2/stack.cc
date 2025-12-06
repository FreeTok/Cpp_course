#include "stack.h"

template <typename T>
Stack<T>::Stack(std::int64_t maxSize) : maxSize(maxSize) {
    if (maxSize < 1)
        throw std::invalid_argument("Stack maxSize < 1");
}

template <typename T>
bool Stack<T>::isEmpty() {
    return data.isEmpty();
}

template <typename T>
void Stack<T>::push(const T& value) {
    if (data.size + 1 > maxSize)
        throw std::overflow_error("Stack overflow");
    data.push_back(value);
}

template <typename T>
T Stack<T>::top() {
    if (data.isEmpty())
        throw std::runtime_error("Stack is empty");
    return data.back();
}

template <typename T>
T Stack<T>::pop() {
    if (data.isEmpty())
        throw std::runtime_error("Stack is empty");

    T val = data.back();
    data.erase(data.size);
    return val;
}

template <typename T>
std::int64_t Stack<T>::size() {
    return data.isEmpty() ? 0 : data.size + 1;
}

template class Stack<int>;
template class Stack<float>;
template class Stack<double>;