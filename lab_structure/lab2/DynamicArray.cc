#include "DynamicArray.h"

#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>

template <typename T>
DynamicArray<T>::DynamicArray() {
  this->capacity = 8;
  this->data = new T[this->capacity];
}

template <typename T>
DynamicArray<T>::DynamicArray(std::int64_t capacity) {
  // check if user is dumb
  if (capacity < 1) {
    throw std::invalid_argument("Capacity < 1"); // https://en.cppreference.com/w/cpp/error/exception.html
    // std::exception like an animal
    // std::invalid_argument like a dog (heir of animal)
  }
  this->capacity = capacity;
  this->data = new T[this->capacity];
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other) {
  this->size = other.size;
  this->capacity = other.capacity;
  this->data = new T[this->capacity]; // (*this).data

  for (int i = 0; i <= size; ++i) {
    this->data[i] = other.data[i];
  }
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
  // deallocate if allocated
  if (this->data) {
    delete[] this->data;
  }
}

template <typename T>
void DynamicArray<T>::push_back(const T& x) {
  // reallocate memory
  // increase capacity
  // copy data
  // dealloc old
  // assign new to old
  if (size + 1 >= capacity) {
    std::int64_t newCapacity = capacity * 2;
    T* tempArray = new T[newCapacity];
    for (int i = 0; i < capacity; ++i) {
      tempArray[i] = data[i];
    }
    delete[] data;
    data = tempArray;
    capacity = newCapacity;
  }
  data[++size] = x;
  // data[size + 1] = x;
  // ++size;
}

template <typename T>
void DynamicArray<T>::push_front(const T& x) {
  if (size + 1 >= capacity) {
    increase_capacity(capacity * 2);
  }

  if (isEmpty()) {
    size = 0;
    data[0] = x;
    return;
  }

  for (std::int64_t i = size; i >= 0; --i) {
    data[i + 1] = data[i];
  }

  data[0] = x;
  ++size;
}

template <typename T>
T DynamicArray<T>::front() {
  if (isEmpty()) {
    throw std::invalid_argument("Empty array");
  }
  return data[0];
}

template <typename T>
T DynamicArray<T>::back() {
  if (isEmpty()) {
    throw std::invalid_argument("Empty array");
  }
  return data[size];
}

template <typename T>
void DynamicArray<T>::insert(std::int64_t idx, const T& x) {
  if (idx < 0) {
    throw std::invalid_argument("idx < 0");
  }

  if (idx > size + 1) {
    throw std::invalid_argument("idx out of range");
  }

  if (size + 1 >= capacity) {
    increase_capacity(capacity * 2);
  }

  for (std::int64_t i = size; i >= idx; --i) {
    data[i + 1] = data[i];
  }

  data[idx] = x;
  ++size;
}

template <typename T>
void DynamicArray<T>::erase(std::int64_t idx) {
  if (isEmpty()) {
    throw std::invalid_argument("Empty array");
  }

  if (idx < 0 || idx > size) {
    throw std::invalid_argument("idx out of range");
  }

  for (std::int64_t i = idx; i < size; ++i) {
    data[i] = data[i + 1];
  }

  --size;
}

template <typename T>
void DynamicArray<T>::erase_after(std::int64_t idx) {
  if (idx < 0) {
    throw std::invalid_argument("idx < 0");
  }

  if (idx >= size || isEmpty()) {
    return;
  }

  size = idx;
}

template <typename T>
void DynamicArray<T>::increase_capacity(std::int64_t newCapacity) {
  if (newCapacity <= capacity) {
    return;
  }

  if (!isEmpty() && newCapacity < size + 1) {
    throw std::invalid_argument("newCapacity is too small for current data");
  }

  T* temp = new T[newCapacity];

  if (!isEmpty()) {
    for (std::int64_t i = 0; i <= size; ++i) {
      temp[i] = data[i];
    }
  }

  delete[] data;
  data = temp;
  capacity = newCapacity;
}

template <typename T>
void DynamicArray<T>::decrease_capacity(std::int64_t newCapacity) {
  if (newCapacity < 1) {
    throw std::invalid_argument("newCapacity < 1");
  }

  if (newCapacity >= capacity || isEmpty()) {
    return;
  }

  std::int64_t newSize = size;
  if (size + 1 > newCapacity) {
    newSize = newCapacity - 1;
  }

  T* temp = new T[newCapacity];

  if (newSize >= 0) {
    for (std::int64_t i = 0; i <= newSize; ++i) {
      temp[i] = data[i];
    }
  }

  delete[] data;
  data = temp;
  capacity = newCapacity;
  size = newSize;
}

template <typename T>
T DynamicArray<T>::add(std::int64_t idx1, std::int64_t idx2) {
  if (idx1 > size || idx2 > size || idx1 < 0 || idx2 < 0) {
    throw std::invalid_argument("idx1 or idx2 out of range");
  }
  return data[idx1] + data[idx2];
}

template <typename T>
T DynamicArray<T>::max() {
  if (isEmpty()) {
    throw std::invalid_argument("Empty array");
  }
  float currentMax = -1e+38; // -1 * 10^38
  // float currentMax = std::numeric_limits<T>::lowest();
  for (int i = 0; i <= size; ++i) {
    if (data[i] >= currentMax) {
      currentMax = data[i];
    }
  }
  return currentMax;
}

template <typename T>
T DynamicArray<T>::min() {
  if (isEmpty()) {
    throw std::invalid_argument("Empty array");
  }
  float currentMin = 1e+38; // -1 * 10^38
  // float currentMin = std::numeric_limits<float>::max();
  for (int i = 0; i <= size; ++i) {
    if (data[i] <= currentMin) {
      currentMin = data[i];
    }
  }
  return currentMin;
}

template <typename T>
void DynamicArray<T>::clear() {
  if (this->data) {
    delete[] this->data;
    this->data = nullptr;
  }
  size = -1;
  capacity = 8;
}

template <typename T>
void DynamicArray<T>::reinitialize() {
  clear();
  data = new T[capacity](); // init with zeros
}

template <typename T>
void DynamicArray<T>::printData() {
  if (isEmpty()) {
    return;
  }
  for (int i = 0; i <= size; ++i) {
    std::cout << data[i] << " ";
  }
  std::cout << std::endl;
}

template <typename T>
T DynamicArray<T>::operator[](std::int64_t idx) {
  if (isEmpty() || idx < 0 || idx > size) {
    throw std::invalid_argument("Out of range");
  }
  return data[size - idx]; // Arabic operator[]
  // return data[idx];     // European operator[]
}

template <typename T>
T DynamicArray<T>::operator()() {
  if (isEmpty()) {
    return 0;
  }
  float sum = 0;
  for (int i = 0; i <= size; ++i) {
    sum += data[i];
  }
  return sum;
}

template class DynamicArray<int>;
template class DynamicArray<float>;
template class DynamicArray<double>;