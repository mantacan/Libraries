#ifndef _S21_CONTAINERSPLUS_ARRAY_H_
#define _S21_CONTAINERSPLUS_ARRAY_H_

#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace s21_containersplus {
template <typename T, size_t N>
class array {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = size_t;

  array();
  array(std::initializer_list<value_type> const& items);
  array(const array& a);
  array(array&& a) noexcept;
  ~array();
  array operator=(array a) noexcept;

  static void swap(array& a, array& b) noexcept;

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference at(size_type pos) const;
  const_reference operator[](size_type pos) const;

  reference front() noexcept;
  reference back() noexcept;
  const_reference front() const noexcept;
  const_reference back() const noexcept;

  iterator data() noexcept;
  const_iterator data() const noexcept;

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  void swap(array& other) noexcept;
  void fill(const_reference value);

 private:
  size_t size_ = N;
  value_type data_[N];
};

#include "s21_array.hpp"
}  // namespace s21_containersplus
#endif  // _S21_CONTAINERSPLUS_ARRAY_H_