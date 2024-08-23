
template <typename T, size_t N>
array<T, N>::array() : size_(N) {}

template <typename T, size_t N>
array<T, N>::array(std::initializer_list<value_type> const& items) : array() {
  size_t i = 0;
  for (auto it = items.begin(); it != items.end(); ++it, ++i) data_[i] = *it;
}

template <typename T, size_t N>
array<T, N>::array(const array& a) {
  if (a.data_) std::copy(a.cbegin(), a.cend(), data_);
}

template <typename T, size_t N>
array<T, N>::array(array&& a) noexcept : size_(a.size_) {
  std::swap(data_, a.data_);
  a.size_ = 0;
}

template <typename T, size_t N>
array<T, N>::~array() {
  ;
}

template <typename T, size_t N>
array<T, N> array<T, N>::operator=(array a) noexcept {
  swap(*this, a);
  return *this;
}

template <typename T, size_t N>
void array<T, N>::swap(array& a, array& b) noexcept {
  using std::swap;
  swap(a.data_, b.data_);
  swap(a.size_, b.size_);
}

template <typename T, size_t N>
void array<T, N>::swap(array& other) noexcept {
  swap(*this, other);
}

template <typename T, size_t N>
typename array<T, N>::const_reference array<T, N>::at(size_type pos) const {
  if (pos < 0 || pos > size_)
    throw std::out_of_range("Incorrect index for array.");
  return data_[pos];
}

template <typename T, size_t N>
typename array<T, N>::const_reference array<T, N>::operator[](
    size_type pos) const {
  return data_[pos];
}

template <typename T, size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if ((!size_ && pos) || pos > size_ - 1)
    throw std::out_of_range("Incorrect index for array.");
  return data_[pos];
}

template <typename T, size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  return data_[pos];
}

template <typename T, size_t N>
typename array<T, N>::reference array<T, N>::front() noexcept {
  return data_[0];
}

template <typename T, size_t N>
typename array<T, N>::reference array<T, N>::back() noexcept {
  return data_[size_ - 1];
}

template <typename T, size_t N>
typename array<T, N>::const_reference array<T, N>::front() const noexcept {
  return data_[0];
}

template <typename T, size_t N>
typename array<T, N>::const_reference array<T, N>::back() const noexcept {
  return data_[size_ - 1];
}

template <typename T, size_t N>
typename array<T, N>::iterator array<T, N>::data() noexcept {
  return data_;
}

template <typename T, size_t N>
typename array<T, N>::const_iterator array<T, N>::data() const noexcept {
  return data_;
}

template <typename T, size_t N>
typename array<T, N>::iterator array<T, N>::begin() {
  return data();
}

template <typename T, size_t N>
typename array<T, N>::iterator array<T, N>::end() {
  return data() + size_;
}

template <typename T, size_t N>
typename array<T, N>::const_iterator array<T, N>::cbegin() const {
  return data();
}

template <typename T, size_t N>
typename array<T, N>::const_iterator array<T, N>::cend() const {
  return data() + size_;
}

template <typename T, size_t N>
bool array<T, N>::empty() const noexcept {
  return size_ ? false : true;
}

template <typename T, size_t N>
typename array<T, N>::size_type array<T, N>::size() const noexcept {
  return size_;
}

template <typename T, size_t N>
typename array<T, N>::size_type array<T, N>::max_size() const noexcept {
  return size();
}

template <typename T, size_t N>
void array<T, N>::fill(const_reference value) {
  std::fill(begin(), end(), value);
}
