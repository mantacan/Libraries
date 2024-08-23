#ifndef S21_CONTAINERS_LIST_H_
#define S21_CONTAINERS_LIST_H_

#include <chrono>
#include <initializer_list>
#include <iostream>
#include <list>
#include <string>

namespace s21 {

template <typename T>
class list {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

 private:
  struct Node {
    T data;
    Node *next;
    Node *prev;

    Node(const T &d) : data(d), next(nullptr), prev(nullptr) {}
  };

  Node *head;
  size_type size_;

  /*
   *
   *
   *
   *
   *
   *
   *    CLASS ITERATOR
   *
   *
   *
   *
   *
   *
   */

 public:
  class ListIterator {
   public:
    ListIterator() : current(nullptr) {}

    explicit ListIterator(Node *node) : current(node) {}

    using reference = T &;

    bool operator==(const ListIterator &other) const;

    bool operator!=(const ListIterator &other) const;

    ListIterator &operator++();

    ListIterator operator++(int);

    reference operator*() const;

    Node *getCurrent() const;

    Node *getNext() const;

    Node *getPrev() const;

   private:
    Node *current;
  };

  /*
   *
   *
   *
   *
   *
   *
   *    CLASS CONST ITERATOR
   *
   *
   *
   *
   *
   *
   */
  class ListConstIterator : public ListIterator {
   public:
    using base = typename list<T>::ListIterator;
    using base::base;
    using reference = const T &;

    const reference operator*() const { return base::operator*(); }
  };

  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

  /*
   *
   *
   *
   *
   *
   *
   *    CLASS LIST : METHODS
   *
   *
   *
   *
   *
   *
   */
 public:
  list() noexcept;

  list(size_t n);

  list(std::initializer_list<T> const &items);

  list(const list &l);

  list(list &&l) noexcept;

  ~list() noexcept;

  list &operator=(list &&l) noexcept;

  Node *getHead() const;

  void setHead(Node *newHead);

  size_type getSize() const;

  void setSize(size_type newSize);

  Node *getNext(Node *node) const;

  void setNext(Node *node, Node *nextNode);

  Node *getPrev(Node *node) const;

  void setPrev(Node *node, Node *prevNode);

  void clear() noexcept;

  iterator insert(iterator pos, const_reference value);

  void erase(iterator pos);

  void push_back(const_reference value);

  void pop_back();

  void push_front(const_reference value);

  void pop_front();

  void swap(list &other);

  void merge(list &other);

  void splice(const_iterator pos, list &other);
  Node *tail() const;

  void reverse();

  void unique();

  void sort();

  const_reference front() const;

  const_reference back() const;

  bool empty() const { return size_ == 0; }

  size_t size() const { return size_; }

  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(Node);
  }

  iterator begin() noexcept { return iterator(head); }

  iterator end() noexcept { return iterator(nullptr); }

  const_iterator begin() const noexcept { return const_iterator(head); }

  const_iterator end() const noexcept { return const_iterator(nullptr); }

  const_iterator c_begin() const noexcept { return const_iterator(head); }

  const_iterator c_end() const noexcept { return const_iterator(nullptr); }

  /*
   * BONUS METHODS
   *
   */

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    return insert_many_impl(pos, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    (push_back(std::forward<Args>(args)), ...);
  }

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    auto insert_front_impl = [this](auto &&...args) {
      (push_front(std::forward<decltype(args)>(args)), ...);
    };
    insert_front_impl(std::forward<Args>(args)...);
  }

 private:
  template <typename Arg>
  iterator insert_many_impl(const_iterator pos, Arg &&arg) {
    return insert(pos, std::forward<Arg>(arg));
  }

  template <typename FirstArg, typename... RestArgs>
  iterator insert_many_impl(const_iterator pos, FirstArg &&firstArg,
                            RestArgs &&...restArgs) {
    insert(pos, std::forward<FirstArg>(firstArg));
    return insert_many_impl(pos, std::forward<RestArgs>(restArgs)...);
  }
};

#include "s21_list.hpp"
}  // namespace s21
#endif
