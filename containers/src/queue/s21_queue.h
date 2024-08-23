#ifndef S21_CONTAINERS_QUEUE_H_
#define S21_CONTAINERS_QUEUE_H_

#include <chrono>
#include <initializer_list>
#include <iostream>
#include <list>
#include <string>

namespace s21 {

template <typename T>
class queue {
 private:
  s21::list<T> data;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  queue() {}
  queue(std::initializer_list<value_type> const &items) : data(items) {}
  queue(const queue &other) = default;
  queue(queue &&other) noexcept = default;
  ~queue() = default;
  queue &operator=(const queue &other) = default;
  queue &operator=(queue &&other) noexcept = default;

  const_reference front();
  const_reference back() const;
  bool empty() const;
  size_type size() const;
  void push(const_reference value);
  void pop();
  void swap(queue &other);

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    (..., push(std::forward<Args>(args)));
  }
};
#include "s21_queue.hpp"
}  // namespace s21

#endif