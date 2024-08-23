#ifndef TESTVECTOR_H
#define TESTVECTOR_H

#include <initializer_list>
#include <iostream>
#include <limits>
#include <utility>

/*
HEADER FILE
*/

// Test vector class with some basic example operations and concepts
namespace s21 {
template <class T>
class Vector {
  // private attributes
 private:
  size_t m_size;
  size_t m_capacity;
  T *arr;
  // public attribures
 public:
  // member types
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;
  // private method
 private:
  void reserve_more_capacity(size_type size);
  // public methods
 public:
  // default constructor (simplified syntax for assigning values to attributes)
  Vector() : m_size(0U), m_capacity(0U), arr(nullptr) {}
  // parametrized constructor for fixed size vector (explicit was used in order
  // to avoid automatic type conversion)
  explicit Vector(size_type n)
      : m_size(n), m_capacity(n), arr(n ? new T[n] : nullptr) {}
  // initializer list constructor (allows creating lists with initializer lists,
  // see main.cpp)
  Vector(std::initializer_list<value_type> const &items);
  // copy constructor with simplified syntax
  Vector(const Vector &v);
  // move constructor with simplified syntax
  Vector(Vector &&v) : m_size(v.m_size), m_capacity(v.m_capacity), arr(v.arr) {
    v.arr = nullptr;
    v.m_size = 0;
  }

  // destructor
  ~Vector() { delete[] arr; }
  void operator=(Vector &&v);
  reference at(size_type pos);
  const_reference at_const(size_type pos) const;
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  iterator begin();
  iterator end();
  size_type size() const;
  size_type max_size();
  void reserve(size_type size);
  bool empty();
  void shrink_to_fit();
  size_type capacity();
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void swap(Vector &other);
  void pop_back();
  T *data();
};
}  // namespace s21
#include "s21_vector.hpp"
#endif
