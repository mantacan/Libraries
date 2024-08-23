/*
IMPLEMENTATION FILE
*/

template <typename T>
void s21::Vector<T>::reserve_more_capacity(s21::Vector<T>::size_type size) {
  if (size > m_capacity) {
    value_type *buff = new value_type[size];
    for (size_type i = 0; i < m_size; ++i) buff[i] = std::move(arr[i]);
    delete[] arr;
    arr = buff;
    m_capacity = size;
  }
}

// initializer list constructor (allows creating lists with initializer lists,
// see main.cpp)
template <typename T>
s21::Vector<T>::Vector(
    std::initializer_list<s21::Vector<T>::value_type> const &items) {
  arr = new value_type[items.size()];
  int i = 0;
  for (auto it = items.begin(); it != items.end(); it++) {
    arr[i] = *it;
    i++;
  }
  m_size = items.size();
  m_capacity = items.size();
};

template <typename T>
void s21::Vector<T>::clear() {
  iterator iter = begin();
  for (size_type i = 0; i < m_size; i++) {
    erase(iter);
    iter++;
  }
  m_size = 0;
  m_capacity = 0;
}

template <typename T>
s21::Vector<T>::Vector(const Vector &v) {
  m_size = 0;
  m_capacity = 0;
  for (size_type i = 0; i < v.size(); i++) push_back(v.at_const(i));
}

template <typename T>
typename s21::Vector<T>::iterator s21::Vector<T>::insert(
    iterator pos, const_reference value) {
  size_type index = m_capacity + 1;
  iterator iter = begin();
  for (size_type i = 0; i < m_size; i++) {
    if (iter == pos) index = i;
    iter++;
  }
  if (index == m_capacity + 1) throw std::out_of_range("invalid pos");
  if (m_capacity <= m_size) reserve(m_size + 1);
  for (size_type i = m_size; i > index; i--) {
    arr[i] = arr[i - 1];
  }
  m_size++;
  arr[index] = value;
  return (&(arr[index]));
}

template <typename T>
void s21::Vector<T>::erase(s21::Vector<T>::iterator pos) {
  size_type index = m_capacity + 1;
  iterator iter = begin();
  for (size_type i = 0; i < m_size; i++) {
    if (iter == pos) index = i;
    iter++;
  }
  if (index == m_capacity + 1) throw std::out_of_range("invalid pos");
  for (size_type i = index; i < m_size - 1; i++) {
    arr[i] = arr[i + 1];
  }
  arr[m_size - 1] = 0;
  m_size--;
}

template <typename T>
size_t s21::Vector<T>::size() const {
  return m_size;
}

template <typename T>
typename s21::Vector<T>::reference s21::Vector<T>::at(size_type pos) {
  if (pos >= m_size) throw std::out_of_range("pos was not found");
  return arr[pos];
}

template <typename T>
typename s21::Vector<T>::const_reference s21::Vector<T>::at_const(
    size_type pos) const {
  if (pos >= m_size) throw std::out_of_range("pos was not found");
  return arr[pos];
}

template <typename T>
typename s21::Vector<T>::reference s21::Vector<T>::operator[](
    Vector<T>::size_type pos) {
  return arr[pos];
}

template <typename T>
typename s21::Vector<T>::const_reference s21::Vector<T>::front() {
  return at(0);
}

template <typename T>
typename s21::Vector<T>::const_reference s21::Vector<T>::back() {
  return at(m_size - 1);
}

template <typename T>
void s21::Vector<T>::push_back(s21::Vector<T>::const_reference value) {
  if (m_size == m_capacity) {
    reserve_more_capacity(m_size + 1);
  }
  arr[m_size++] = value;
}

template <typename T>
void s21::Vector<T>::pop_back() {
  erase(end());
}

template <typename T>
void s21::Vector<T>::swap(s21::Vector<T> &other) {
  Vector temp;
  for (size_type i = 0; i < other.size(); i++) temp.push_back(other[i]);
  other.clear();
  for (size_type i = 0; i < m_size; i++) other.push_back(arr[i]);
  clear();
  for (size_type i = 0; i < temp.size(); i++) push_back(temp[i]);
}

template <typename T>
void s21::Vector<T>::operator=(s21::Vector<T> &&v) {
  clear();
  for (size_type i = 0; i < v.m_size; i++) push_back(v[i]);
  v.~Vector();
}

template <typename T>
bool s21::Vector<T>::empty() {
  return m_size == 0;
}

template <typename T>
typename s21::Vector<T>::size_type s21::Vector<T>::capacity() {
  return m_capacity;
}

template <typename T>
T *s21::Vector<T>::data() {
  return arr;
}

template <typename T>
typename s21::Vector<T>::iterator s21::Vector<T>::begin() {
  return arr;
}

template <typename T>
typename s21::Vector<T>::iterator s21::Vector<T>::end() {
  return arr + (m_size - 1);
}

template <typename T>
typename s21::Vector<T>::size_type s21::Vector<T>::max_size() {
  return std::numeric_limits<size_type>::max();
}

template <typename T>
void s21::Vector<T>::reserve(s21::Vector<T>::size_type size) {
  reserve_more_capacity(size);
}

template <typename T>
void s21::Vector<T>::shrink_to_fit() {
  size_type size = m_size;
  value_type *buff = new value_type[size];
  for (size_type i = 0; i < m_size; ++i) buff[i] = std::move(arr[i]);
  delete[] arr;
  arr = buff;
  m_capacity = size;
}
// externalizing template instances for correct linking, feel free to find more
// information
template class s21::Vector<int>;
