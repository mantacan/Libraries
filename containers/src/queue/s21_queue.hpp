template <typename T>
typename queue<T>::const_reference queue<T>::front() {
  return data.front();
}

template <typename T>
typename queue<T>::const_reference queue<T>::back() const {
  return data.back();
}

template <typename T>
bool queue<T>::empty() const {
  return data.empty();
}

template <typename T>
typename queue<T>::size_type queue<T>::size() const {
  return data.size();
}

template <typename T>
void queue<T>::push(const_reference value) {
  data.push_back(value);
}

template <typename T>
void queue<T>::pop() {
  if (empty()) {
    throw std::out_of_range("queue is empty");
  }
  data.pop_front();
}

template <typename T>
void queue<T>::swap(queue &other) {
  data.swap(other.data);
}
