#ifndef _S21_MAP_H_
#define _S21_MAP_H_
#include <initializer_list>
#include <iostream>
#include <utility>
#include <vector>

#define RED 1
#define BLACK 0
#define LEFT 0
#define RIGHT 1

namespace s21 {
template <class key_type, class mapped_type>
class BinaryTree {
 public:
  using value_type = std::pair<key_type, mapped_type>;

 private:
  bool color_;  // where 0 is "black", 1 is "red"
  value_type value_;
  BinaryTree *left_;
  BinaryTree *right_;
  BinaryTree *parent_;

 public:
  BinaryTree();
  ~BinaryTree();
  void setRight(BinaryTree *ptr);
  void setLeft(BinaryTree *ptr);
  void setParent(BinaryTree *ptr);
  void setColor(bool color);
  bool getColor() const;
  BinaryTree *getRight() const;
  BinaryTree *getLeft() const;
  BinaryTree *getParent() const;
  void setValue(value_type value);
  value_type &getValue();
};

template <class key_type, class mapped_type>
class MapIterator {
 private:
  BinaryTree<key_type, mapped_type> *current_;

 public:
  using value_type = std::pair<const key_type, mapped_type>;
  MapIterator();
  MapIterator(BinaryTree<key_type, mapped_type> *ptr);
  ~MapIterator();
  void operator=(BinaryTree<key_type, mapped_type> *ptr);
  bool operator==(const MapIterator &other) const;
  bool operator!=(const MapIterator &other) const;
  void operator++();
  void operator--();
  void goToKey(key_type key);
  void goToRoot();
  void goLeft();
  void goRight();
  void goUp();
  BinaryTree<key_type, mapped_type> *getNodePtr() const;
  value_type operator*() const;
};
template <class key_type, class mapped_type>
class MapConstIterator {
 private:
  BinaryTree<key_type, mapped_type> *current_;

 public:
  using value_type = std::pair<const key_type, mapped_type>;
  MapConstIterator();
  MapConstIterator(BinaryTree<key_type, mapped_type> *ptr);
  ~MapConstIterator();
  void operator=(BinaryTree<key_type, mapped_type> *ptr);
  bool operator==(const MapConstIterator &other) const;
  bool operator!=(const MapConstIterator &other) const;
  void operator++();
  void operator--();
  void goToKey(key_type key);
  void goToRoot();
  void goLeft();
  void goRight();
  void goUp();
  const value_type operator*() const;
  BinaryTree<key_type, mapped_type> *getNodePtr() const;
};
template <class Key, class T>
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = s21::MapIterator<key_type, mapped_type>;
  using const_iterator = s21::MapConstIterator<key_type, mapped_type>;
  using size_type = size_t;

  map();
  map(std::initializer_list<value_type> const &items);
  map(const map &m);
  map(map &&m);
  ~map();
  map operator=(map &&m);
  map operator=(const map &m);
  T &at(const key_type &key);
  T &operator[](const key_type &key);

  iterator begin();
  iterator end();
  const_iterator const_begin() const;
  const_iterator const_end() const;

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const key_type &key, const T &obj);
  std::pair<iterator, bool> insert_or_assign(const key_type &key, const T &obj);
  void erase(iterator pos);
  void swap(map &other);
  void merge(const map &other);
  s21::BinaryTree<key_type, mapped_type> *getRoot() const;
  bool contains(const key_type &key);
  s21::BinaryTree<key_type, mapped_type> root() const;
  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

 private:
  size_type size_;
  s21::BinaryTree<key_type, mapped_type> *root_;
  void destroy_tree();
  void default_destructor();
  void createNewNode(s21::map<key_type, mapped_type>::iterator *iter,
                     std::pair<key_type, mapped_type> value);
  void rebalance_insert(BinaryTree<key_type, mapped_type> *newNode);
  void rebalance_erase(BinaryTree<key_type, mapped_type> *node);
  bool recolor(BinaryTree<key_type, mapped_type> *node);
  void rotate(BinaryTree<key_type, mapped_type> *node);
  void rotate_in_direction(BinaryTree<key_type, mapped_type> *node,
                           bool direction);
  std::pair<iterator, bool> default_insert(const value_type &value);
  void eraseIfHaveBothChildrenInErase(
      BinaryTree<key_type, mapped_type> *&replacingNode,
      BinaryTree<key_type, mapped_type> *nodeToDelete);
};
#include "s21_map.hpp"
}  // namespace s21
#endif