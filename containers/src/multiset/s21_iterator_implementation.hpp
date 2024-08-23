
template <typename ValueType, typename Compare>
IteratorImplementation<ValueType, Compare>::IteratorImplementation(
    NodeBT<ValueType>* source)
    : node_(source) {
  if (source)
    count_ = source->node_count_;
  else
    count_ = 0;
}

template <typename ValueType, typename Compare>
IteratorImplementation<ValueType, Compare>::IteratorImplementation(
    const IteratorImplementation& source)
    : node_(source.node_), count_(source.count_) {}

template <typename ValueType, typename Compare>
void IteratorImplementation<ValueType, Compare>::swap(
    IteratorImplementation& iter) noexcept {
  using std::swap;
  swap(node_, iter.node_);
  swap(count_, iter.count_);
}

template <typename ValueType, typename Compare>
IteratorImplementation<ValueType, Compare>&
IteratorImplementation<ValueType, Compare>::operator=(
    IteratorImplementation iter) {
  swap(iter);
  return *this;
}

template <typename ValueType, typename Compare>
ValueType& IteratorImplementation<ValueType, Compare>::operator*() {
  return node_->node_value_;
}

template <typename ValueType, typename Compare>
ValueType const& IteratorImplementation<ValueType, Compare>::operator*() const {
  return node_->node_value_;
}

template <typename ValueType, typename Compare>
bool IteratorImplementation<ValueType, Compare>::is_max() const {
  if (!node_) return true;
  IteratorImplementation it(*this);
  bool ret_value = false;
  while (it.node_ && it.node_->node_parent_ &&
         it.node_ == it.node_->node_parent_->node_right_)
    it.node_ = it.node_->node_parent_;
  if (it.node_->node_parent_)
    ret_value = false;
  else
    ret_value = true;
  return ret_value;
}

template <typename ValueType, typename Compare>
IteratorImplementation<ValueType, Compare>
IteratorImplementation<ValueType, Compare>::operator++() {
  if (!node_) return *this;

  if (count_ > 1) {
    --count_;
    return *this;
  }

  if (node_->node_right_) {
    node_ = node_->node_right_;
    while (node_->node_left_) node_ = node_->node_left_;
  } else if (is_max()) {
    node_ = nullptr;
    count_ = 0;

  } else {
    NodeBT<ValueType>* parent_ = node_->node_parent_;
    while (parent_ && node_ == parent_->node_right_) {
      node_ = parent_;
      parent_ = parent_->node_parent_;
    }
    node_ = parent_;
  }
  count_ = node_ ? node_->node_count_ : 0;

  return *this;
}

template <typename ValueType, typename Compare>
IteratorImplementation<ValueType, Compare>
IteratorImplementation<ValueType, Compare>::operator++(int) {
  IteratorImplementation it(*this);
  ++(*this);
  return it;
}

template <typename ValueType, typename Compare>
IteratorImplementation<ValueType, Compare>
IteratorImplementation<ValueType, Compare>::operator--() {
  if (!node_) return *this;

  if (count_ > 1) {
    --count_;
    return *this;
  }

  if (node_->node_left_) {
    node_ = node_->node_left_;
    while (node_->node_right_) node_ = node_->node_right_;
    // } else if (node_ == getRoot().max().getNodePointer()) {
    //     node_ = nullptr;
  } else {
    NodeBT<ValueType>* parent_ = node_->node_parent_;
    while (parent_ && node_ == parent_->node_left_) {
      node_ = parent_;
      parent_ = parent_->node_parent_;
    }
    node_ = parent_;
  }
  count_ = node_ ? node_->node_count_ : 0;

  return *this;
}

template <typename ValueType, typename Compare>
IteratorImplementation<ValueType, Compare>
IteratorImplementation<ValueType, Compare>::operator--(int) {
  IteratorImplementation it(*this);
  --(*this);
  return it;
}
