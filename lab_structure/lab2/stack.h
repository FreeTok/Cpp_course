#ifndef STACK_H
#define STACK_H

#include <stdexcept>
#include "DynamicArray.h"

template <typename T>
class Stack {
private:
    DynamicArray<T> data;
    std::int64_t maxSize;

public:
    Stack(std::int64_t maxSize = 100);
    std::int64_t size();

    bool isEmpty();
    void push(const T& value);
    T top();
    T pop();
};

extern template class Stack<int>;
extern template class Stack<float>;
extern template class Stack<double>;

#endif // STACK_H