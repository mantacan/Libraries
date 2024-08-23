
template <typename ValueType>
NodeBT<ValueType>::NodeBT(const NodeBT& source)
    : node_value_(source.node_value_),
      node_count_(source.node_count_),
      node_parent_(source.node_parent_),
      node_left_(source.node_left_),
      node_right_(source.node_right_) {}

template <typename ValueType>
NodeBT<ValueType>::NodeBT(const ValueType& source)
    : node_value_(source), node_count_(1) {}

template <typename ValueType>
NodeBT<ValueType>& NodeBT<ValueType>::operator=(NodeBT source) {
  swap(source);
  return *this;
}

template <typename ValueType>
void NodeBT<ValueType>::swap(NodeBT& source) noexcept {
  using std::swap;
  swap(node_value_, source.node_value_);
  swap(node_count_, source.node_count_);
  swap(node_parent_, source.node_parent_);
  swap(node_left_, source.node_left_);
  swap(node_right_, source.node_right_);
}
