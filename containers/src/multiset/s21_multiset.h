#ifndef _S21_CONTAINERSPLUS_MULTISET_H_
#define _S21_CONTAINERSPLUS_MULTISET_H_

#include <limits.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

namespace s21_containersplus {

template <typename Key, typename Compare = std::less<Key>>
class multiset;

template <typename ValueType, typename Compare = std::less<ValueType>>
class MultisetIterator;

template <typename ValueType, typename Compare = std::less<ValueType>>
class MultisetConstIterator;

template <typename ValueType>
struct NodeBT /*NodeBinaryTree*/ {
 public:
  explicit NodeBT(const NodeBT& source);
  explicit NodeBT(const ValueType& source);
  NodeBT& operator=(NodeBT source);

 public:
  ValueType node_value_;
  size_t node_count_ = 0;
  NodeBT* node_parent_ = nullptr;
  NodeBT* node_left_ = nullptr;
  NodeBT* node_right_ = nullptr;

  void swap(NodeBT& source) noexcept;
};

#include "s21_node_binary_tree.hpp"

template <typename ValueType, typename Compare = std::less<ValueType>>
class IteratorImplementation {
 public:
  IteratorImplementation() = default;
  explicit IteratorImplementation(NodeBT<ValueType>* source);
  IteratorImplementation(const IteratorImplementation& source);
  IteratorImplementation& operator=(IteratorImplementation iter);

  ValueType& operator*();
  const ValueType& operator*() const;

  IteratorImplementation operator++();
  IteratorImplementation operator++(int);
  IteratorImplementation operator--();
  IteratorImplementation operator--(int);

  bool operator==(const IteratorImplementation& it) const {
    return node_ == it.node_ && count_ == it.count_;
  }
  bool operator==(const ValueType& value) const {
    return node_->node_value_ == value;
  }
  bool operator!=(const IteratorImplementation& it) const {
    return node_ !=
           it.node_ /*&& count_ != it.count_*/;  // count breaks destructor
  }

  friend multiset<ValueType, Compare>;

 private:
  NodeBT<ValueType>* node_ = nullptr;
  size_t count_ = 0;

  friend class MultisetIterator<ValueType, Compare>;
  friend class MultisetConstIterator<ValueType, Compare>;

  void swap(IteratorImplementation& iter) noexcept;

  bool is_max() const;
  bool is_this_exist() const { return node_; }
  bool is_this_left() const {
    return node_ && node_->node_parent_ &&
           node_ == node_->node_parent_->node_left_;
  }
  bool is_right_exist() const { return node_ && node_->node_right_; }
  bool is_parent_exist() const { return node_ && node_->node_parent_; }
  bool is_left_exist() const { return node_ && node_->node_left_; }
};

#include "s21_iterator_implementation.hpp"

template <typename ValueType, typename Compare /*= std::less<ValueType>*/>
class MultisetIterator {
 public:
  MultisetIterator() = default;
  MultisetIterator(const MultisetIterator& it);
  MultisetIterator(NodeBT<ValueType>* source);
  MultisetIterator(const IteratorImplementation<ValueType, Compare>& it);
  MultisetIterator& operator=(MultisetIterator it);

  operator IteratorImplementation<ValueType, Compare>() { return my_it; }

  ValueType& operator*() { return *my_it; }

  MultisetIterator operator++() { return ++my_it; }
  MultisetIterator operator++(int) { return my_it++; }
  MultisetIterator operator--() { return --my_it; }
  MultisetIterator operator--(int) { return my_it--; }
  bool operator==(const MultisetIterator& it) const {
    return this->my_it == it.my_it;
  }
  bool operator==(const ValueType& value) const { return this->my_it == value; }
  bool operator!=(const MultisetIterator& it) const {
    return this->my_it != it.my_it;
  }

  ValueType& value() { return *my_it; }

  friend multiset<ValueType, Compare>;

 private:
  IteratorImplementation<ValueType, Compare> my_it;

  NodeBT<ValueType>* operator->() { return (my_it.node_); }
  bool is_this_exist() const { return my_it.is_this_exist(); }

  void swap(MultisetIterator& it) noexcept;
};

#include "s21_iterator.hpp"

template <typename ValueType, typename Compare /*= std::less<ValueType>*/>
class MultisetConstIterator {
 public:
  MultisetConstIterator() = default;
  MultisetConstIterator(const MultisetConstIterator& it);
  MultisetConstIterator(NodeBT<ValueType>* source);
  MultisetConstIterator(const IteratorImplementation<ValueType, Compare>& it);
  MultisetConstIterator& operator=(MultisetConstIterator it);

  operator IteratorImplementation<ValueType, Compare>() { return my_it; }

  // ValueType& operator*() { return *my_it; }
  const ValueType& operator*() const { return *my_it; }

  MultisetConstIterator operator++() { return ++my_it; }
  MultisetConstIterator operator++(int) { return my_it++; }
  MultisetConstIterator operator--() { return --my_it; }
  MultisetConstIterator operator--(int) { return my_it--; }
  bool operator==(const MultisetConstIterator& it) const {
    return this->my_it == it.my_it;
  }
  bool operator==(const ValueType& value) const { return this->my_it == value; }
  bool operator!=(const MultisetConstIterator& it) const {
    return this->my_it != it.my_it;
  }

  const ValueType& value() { return *my_it; }

  friend multiset<ValueType, Compare>;

 private:
  IteratorImplementation<ValueType, Compare> my_it;

  NodeBT<ValueType>* operator->() { return (my_it.node_); }
  bool is_this_exist() const { return my_it.is_this_exist(); }

  void swap(MultisetConstIterator& it) noexcept;
};

#include "s21_constiterator.hpp"

template <typename Key, typename Compare /*= std::less<Key> */>
class multiset {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = MultisetIterator<Key, Compare>;
  using const_iterator = MultisetConstIterator<Key, Compare>;
  using size_type = size_t;

  multiset() = default;
  multiset(std::initializer_list<value_type> const& items);
  multiset(const multiset& other);
  multiset(multiset&& other);
  ~multiset();

  multiset& operator=(multiset other);

  void swap(multiset& other) noexcept;

  iterator begin() const;
  iterator end() const;
  const_iterator cbegin() const;
  const_iterator cend() const;
  iterator min() const;
  iterator max() const;
  const_iterator cmin() const;
  const_iterator cmax() const;

  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  void clear();
  iterator insert(const value_type& value);
  iterator insert(const IteratorImplementation<value_type, Compare>& it);
  void erase(iterator pos);
  void merge(multiset& other);

  iterator find(const value_type& key) const;
  bool contains(const value_type& key) const;
  auto equal_range(const value_type& key);
  iterator lower_bound(const value_type& key);
  iterator upper_bound(const value_type& key);

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);

  iterator operator[](const value_type& value);

 private:
  NodeBT<value_type>* root_ = nullptr; /*Node Binary Tree*/
  size_type size_ = 0;

  iterator find_like_search(const value_type& value) const;
  // returns iterator on existed elem or iterator on leaf
};

#include "s21_multiset.hpp"

}  // namespace s21_containersplus

#endif  // _S21_CONTAINERSPLUS_MULTISET_H_