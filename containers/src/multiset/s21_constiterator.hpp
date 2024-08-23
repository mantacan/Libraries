
template <typename ValueType, typename Compare>
MultisetConstIterator<ValueType, Compare>::MultisetConstIterator(
    const MultisetConstIterator& it)
    : my_it(it.my_it) {}

template <typename ValueType, typename Compare>
MultisetConstIterator<ValueType, Compare>::MultisetConstIterator(
    NodeBT<ValueType>* source)
    : my_it(source) {}

template <typename ValueType, typename Compare>
MultisetConstIterator<ValueType, Compare>::MultisetConstIterator(
    const IteratorImplementation<ValueType, Compare>& it)
    : my_it(it) {}

template <typename ValueType, typename Compare>
void MultisetConstIterator<ValueType, Compare>::swap(
    MultisetConstIterator& it) noexcept {
  using std::swap;
  swap(my_it.node_, it.my_it.node_);
  swap(my_it.count_, it.my_it.count_);
}

template <typename ValueType, typename Compare>
MultisetConstIterator<ValueType, Compare>&
MultisetConstIterator<ValueType, Compare>::operator=(MultisetConstIterator it) {
  swap(it);
  return *this;
}
