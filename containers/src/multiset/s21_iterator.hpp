
template <typename ValueType, typename Compare>
MultisetIterator<ValueType, Compare>::MultisetIterator(
    const MultisetIterator& it)
    : my_it(it.my_it) {}

template <typename ValueType, typename Compare>
MultisetIterator<ValueType, Compare>::MultisetIterator(
    NodeBT<ValueType>* source)
    : my_it(source) {}

template <typename ValueType, typename Compare>
MultisetIterator<ValueType, Compare>::MultisetIterator(
    const IteratorImplementation<ValueType, Compare>& it)
    : my_it(it) {}

template <typename ValueType, typename Compare>
void MultisetIterator<ValueType, Compare>::swap(MultisetIterator& it) noexcept {
  using std::swap;
  swap(my_it.node_, it.my_it.node_);
  swap(my_it.count_, it.my_it.count_);
}

template <typename ValueType, typename Compare>
MultisetIterator<ValueType, Compare>&
MultisetIterator<ValueType, Compare>::operator=(MultisetIterator it) {
  swap(it);
  return *this;
}
