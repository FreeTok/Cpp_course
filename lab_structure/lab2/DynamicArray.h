#ifndef DYN_ARR_H
#define DYN_ARR_H

#include <cstdint>
// size_t == unsigned long long

template <typename T>
class DynamicArray {
private:
  T* data;
public:
  DynamicArray(); // default ctor
  DynamicArray(std::int64_t capacity); // parametrized ctor
  DynamicArray(const DynamicArray<T>& other);
  ~DynamicArray(); // destructor

  std::int64_t size = -1; // actual (last occupied)
  std::int64_t capacity; // max

  bool isEmpty() {
    return size == -1;
  }

  void push_back(const T& x);

  void push_front(const T& x);
  T front();
  T back();
  void insert(std::int64_t idx, const T& x);
  void erase(std::int64_t idx);
  void erase_after(std::int64_t idx);
  void increase_capacity(std::int64_t newCapacity);
  void decrease_capacity(std::int64_t newCapacity);


  T add(std::int64_t idx1, std::int64_t idx2);
  T max();
  T min();
  void clear(); // deallocate the data
  void reinitialize(); // restore to default
  void printData();

  T operator[](std::int64_t idx);
  T operator()();
};

extern template class DynamicArray<int>;
extern template class DynamicArray<float>;
extern template class DynamicArray<double>;

#endif // DYN_ARR_H