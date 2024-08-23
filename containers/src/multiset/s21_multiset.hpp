
template <typename Key, typename Compare>
multiset<Key, Compare>::multiset(
    std::initializer_list<value_type> const& items) {
  for (auto it = items.begin(), it_end = items.end(); it != it_end; ++it)
    insert(*it);
}

template <typename Key, typename Compare>
multiset<Key, Compare>::multiset(const multiset& other) {
  size_t size_count = 0;
  for (auto it = other.cbegin(), it_end = other.cend(); it != it_end;
       ++it, ++size_count)
    insert(it);
}

template <typename Key, typename Compare>
multiset<Key, Compare>::multiset(multiset&& other)
    : root_(other.root_), size_(other.size_) {
  other.root_ = nullptr;
  other.size_ = 0;
}

template <typename Key, typename Compare>
multiset<Key, Compare>::~multiset() {
  clear();
}

template <typename Key, typename Compare>
multiset<Key, Compare>& multiset<Key, Compare>::operator=(multiset other) {
  swap(other);
  return *this;
}

template <typename Key, typename Compare>
void multiset<Key, Compare>::swap(multiset& other) noexcept {
  using std::swap;
  swap(root_, other.root_);
  swap(size_, other.size_);
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::iterator multiset<Key, Compare>::begin()
    const {
  if (!root_) return end();
  iterator it(root_);
  while (it->node_left_) it.my_it.node_ = it->node_left_;
  it.my_it.count_ = it->node_count_;
  return it;
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::const_iterator multiset<Key, Compare>::cbegin()
    const {
  if (!root_) return cend();
  const_iterator it(root_);
  while (it->node_left_) it.my_it.node_ = it->node_left_;
  it.my_it.count_ = it->node_count_;
  return it;
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::iterator multiset<Key, Compare>::end() const {
  return iterator(nullptr);
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::const_iterator multiset<Key, Compare>::cend()
    const {
  return const_iterator(nullptr);
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::iterator multiset<Key, Compare>::min() const {
  iterator it(root_);
  while (it.is_this_exist() && it->node_left_) it.my_it.node_ = it->node_left_;
  return it;
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::iterator multiset<Key, Compare>::max() const {
  iterator it(root_);
  while (it.is_this_exist() && it->node_right_)
    it.my_it.node_ = it->node_right_;
  return it;
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::const_iterator multiset<Key, Compare>::cmin()
    const {
  const_iterator it(root_);
  while (it.is_this_exist() && it->node_left_) it.my_it.node_ = it->node_left_;
  return it;
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::const_iterator multiset<Key, Compare>::cmax()
    const {
  const_iterator it(root_);
  while (it.is_this_exist() && it->node_right_)
    it.my_it.node_ = it->node_right_;
  return it;
}

template <typename Key, typename Compare>
bool multiset<Key, Compare>::empty() const {
  return !size_;
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::size_type multiset<Key, Compare>::size()
    const {
  return size_;
}

template <typename Key, typename Compare>
size_t multiset<Key, Compare>::max_size() const {
  return SIZE_MAX / sizeof(Key);
}

template <typename Key, typename Compare>
void multiset<Key, Compare>::clear() {
  if (!root_) return;

  for (auto it = begin(), it_end = end(); it != it_end;) erase(it++);

  root_ = nullptr;
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::iterator multiset<Key, Compare>::insert(
    const value_type& value) {
  iterator it_ret;
  if (empty()) {
    root_ = new NodeBT<value_type>(value);
    it_ret = root_;
  } else {
    it_ret = find_like_search(value);
    if (*it_ret == value)
      it_ret->node_count_++;
    else {
      NodeBT<value_type>* p_nbt = new NodeBT<value_type>(value);

      p_nbt->node_parent_ = it_ret.my_it.node_;
      if (Compare()(value, *it_ret))
        it_ret->node_left_ = p_nbt;
      else
        it_ret->node_right_ = p_nbt;
      it_ret.my_it.node_ = p_nbt;
      it_ret.my_it.count_++;
    }
  }
  ++size_;
  return it_ret;
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::iterator multiset<Key, Compare>::insert(
    const IteratorImplementation<value_type, Compare>& it) {
  // iterator it_ret;
  // if (it.count_) it_ret = insert(*it);
  return insert(*it);
}

template <typename Key, typename Compare>
void multiset<Key, Compare>::erase(iterator pos) {
  if (!pos.is_this_exist()) return;

  if (pos.my_it.count_ > 1) {
    // pos.my_it.count_--;
    pos->node_count_--;
  } else {
    if (!(pos.my_it.is_left_exist() || pos.my_it.is_right_exist())) {
      iterator it(pos->node_parent_);

      if (it.my_it.is_this_exist()) {
        if (Compare()(*it, *pos))
          it->node_right_ = nullptr;
        else
          it->node_left_ = nullptr;
      }

    } else if (pos.my_it.is_left_exist() ^ pos.my_it.is_right_exist()) {
      iterator it(pos->node_parent_);

      if (pos.my_it.is_left_exist()) {
        if (it.my_it.is_this_exist()) {
          if (pos.my_it.is_this_left())
            it->node_left_ = pos->node_left_;
          else
            it->node_right_ = pos->node_left_;
        }

        pos->node_left_->node_parent_ = pos->node_parent_;

      } else {
        if (it.my_it.is_this_exist()) {
          if (pos.my_it.is_this_left())
            it->node_left_ = pos->node_right_;
          else
            it->node_right_ = pos->node_right_;
        }

        pos->node_right_->node_parent_ = pos->node_parent_;
      }

    } else if (pos.my_it.is_left_exist() && pos.my_it.is_right_exist()) {
      iterator it(pos->node_right_);

      while (it->node_left_) it.my_it.node_ = it->node_left_;

      if (it->node_parent_) {
        if (Compare()(*it, it->node_parent_->node_value_))
          it->node_parent_->node_left_ = it->node_right_;
        else
          it->node_parent_->node_right_ = it->node_right_;
      }

      std::swap(*pos, *it);
      pos.swap(it);
    }
    delete pos.my_it.node_;
  }
  --size_;
}

template <typename Key, typename Compare>
void multiset<Key, Compare>::merge(multiset& other) {
  for (iterator it = other.begin(), it_end = other.end(); it != it_end; ++it)
    insert(it);

  other.clear();
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::iterator
multiset<Key, Compare>::find_like_search(const value_type& value) const {
  if (!root_) return end();

  iterator it(root_);
  bool flag_stop = false;
  while (it.is_this_exist() && !flag_stop) {
    if (*it == value)
      break;
    else if (Compare()(value, *it)) {
      if (it->node_left_)
        it.my_it.node_ = it->node_left_;
      else
        flag_stop = true;
    } else {
      if (it->node_right_)
        it.my_it.node_ = it->node_right_;
      else
        flag_stop = true;
    }
  }
  it.my_it.count_ = it.is_this_exist() ? it->node_count_ : 0;
  return it;
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::iterator multiset<Key, Compare>::find(
    const value_type& key) const {
  iterator it = find_like_search(key);
  if (*it != key) it = end();
  return it;
}

template <typename Key, typename Compare>
bool multiset<Key, Compare>::contains(const value_type& key) const {
  return find(key) != end();
}

template <typename Key, typename Compare>
auto multiset<Key, Compare>::equal_range(const value_type& key) {
  iterator first = find(key);
  iterator second = first;
  while (second.is_this_exist() && *second == key) ++second;
  return std::pair(first, second);
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::iterator multiset<Key, Compare>::lower_bound(
    const value_type& key) {
  iterator it(root_), it_end = end();
  while (it != it_end) {
    if (it == key)
      break;
    else if (Compare()(*it, key))
      ++it;
    else {
      --it;
      break;
    }
  }
  return it;
}

template <typename Key, typename Compare>
template <typename... Args>
std::vector<std::pair<typename multiset<Key, Compare>::iterator, bool>>
multiset<Key, Compare>::insert_many(Args&&... args) {
  std::vector<std::pair<iterator, bool>> ret_vector = {
      (std::pair(this->insert(args), true))...};
  return ret_vector;
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::iterator multiset<Key, Compare>::operator[](
    const value_type& value) {
  return find(value);
}

template <typename Key, typename Compare>
typename multiset<Key, Compare>::iterator multiset<Key, Compare>::upper_bound(
    const value_type& key) {
  return ++lower_bound(key);
}
