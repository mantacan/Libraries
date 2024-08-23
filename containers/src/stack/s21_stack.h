#ifndef S21_STACK_H_
#define S21_STACK_H_

#include "../list/s21_list.h"

namespace s21 {
template <typename T, class Container = s21::list<T>>
class Stack {
 private:
  Container OnList;

 public:
  using value_type = typename Container::value_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;

  Stack() : OnList() {}
  Stack(std::initializer_list<value_type> const& items) : OnList(items) {}
  Stack(const Stack& s) : OnList(s.OnList) {}
  Stack(Stack&& s) : OnList(std::move(s.OnList)) {}
  ~Stack() {}

  Stack& operator=(Stack&& s) noexcept {
    OnList = std::move(s.OnList);
    return *this;
  }

  const_reference top() { return OnList.back(); }
  bool empty() { return OnList.empty(); }
  size_type size() { return OnList.size(); }
  void push(const_reference value) { this->OnList.push_back(value); }
  void pop() { this->OnList.pop_back(); }
  void swap(Stack* other) { this->OnList.swap(other.OnList); }
  template <class... Args>
  decltype(auto) insert_many_front(Args&&... args) {
    OnList.insert_many_back(std::forward<Args>(args)...);
  }
};
}  // namespace s21

#endif  // S21_STACK_H_
