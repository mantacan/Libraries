/*binary tree*/
template <class key_type, class mapped_type>
s21::BinaryTree<key_type, mapped_type>::BinaryTree() {
  left_ = nullptr;
  right_ = nullptr;
  parent_ = nullptr;
  color_ = RED;
}

template <class key_type, class mapped_type>
s21::BinaryTree<key_type, mapped_type>::~BinaryTree() {
  left_ = nullptr;
  right_ = nullptr;
  parent_ = nullptr;
  color_ = RED;
}

template <class key_type, class mapped_type>
void s21::BinaryTree<key_type, mapped_type>::setRight(BinaryTree* ptr) {
  right_ = ptr;
}

template <class key_type, class mapped_type>
void s21::BinaryTree<key_type, mapped_type>::setLeft(BinaryTree* ptr) {
  left_ = ptr;
}

template <class key_type, class mapped_type>
void s21::BinaryTree<key_type, mapped_type>::setParent(BinaryTree* ptr) {
  parent_ = ptr;
}
template <class key_type, class mapped_type>
void s21::BinaryTree<key_type, mapped_type>::setValue(value_type value) {
  value_.first = value.first;
  value_.second = value.second;
}

template <class key_type, class mapped_type>
typename s21::BinaryTree<key_type, mapped_type>::value_type&
s21::BinaryTree<key_type, mapped_type>::getValue() {
  return value_;
}

template <class key_type, class mapped_type>
s21::BinaryTree<key_type, mapped_type>*
s21::BinaryTree<key_type, mapped_type>::getLeft() const {
  return left_;
}

template <class key_type, class mapped_type>
s21::BinaryTree<key_type, mapped_type>*
s21::BinaryTree<key_type, mapped_type>::getRight() const {
  return right_;
}

template <class key_type, class mapped_type>
s21::BinaryTree<key_type, mapped_type>*
s21::BinaryTree<key_type, mapped_type>::getParent() const {
  return parent_;
}

template <class key_type, class mapped_type>
bool s21::BinaryTree<key_type, mapped_type>::getColor() const {
  return color_;
}

template <class key_type, class mapped_type>
void s21::BinaryTree<key_type, mapped_type>::setColor(bool color) {
  color_ = color;
}

/*map iterator*/
template <class key_type, class mapped_type>
s21::MapIterator<key_type, mapped_type>::MapIterator() {
  current_ = nullptr;
}

template <class key_type, class mapped_type>
s21::MapIterator<key_type, mapped_type>::MapIterator(
    BinaryTree<key_type, mapped_type>* ptr) {
  current_ = ptr;
}

template <class key_type, class mapped_type>
s21::MapIterator<key_type, mapped_type>::~MapIterator() {
  current_ = nullptr;
}

template <class key_type, class mapped_type>
void s21::MapIterator<key_type, mapped_type>::operator=(
    BinaryTree<key_type, mapped_type>* ptr) {
  current_ = ptr;
}

template <class key_type, class mapped_type>
bool s21::MapIterator<key_type, mapped_type>::operator==(
    const MapIterator& other) const {
  return current_ == other.getNodePtr();
}

template <class key_type, class mapped_type>
bool s21::MapIterator<key_type, mapped_type>::operator!=(
    const MapIterator& other) const {
  return current_ != other.getNodePtr();
}

template <class key_type, class mapped_type>
void s21::MapIterator<key_type, mapped_type>::goToRoot() {
  while (current_->getParent() != nullptr) current_ = current_->getParent();
}

template <class key_type, class mapped_type>
void s21::MapIterator<key_type, mapped_type>::operator++() {
  BinaryTree<key_type, mapped_type>* old_node = current_;
  if (current_->getRight() != nullptr) {
    goRight();
    while (current_->getLeft() != nullptr) goLeft();
  } else {
    while (current_->getParent() != nullptr &&
           current_ == current_->getParent()->getRight())
      goUp();
    if (current_->getParent() == nullptr)
      current_ = nullptr;
    else
      goUp();
  }
  if (current_ == nullptr) current_ = old_node;
}

template <class key_type, class mapped_type>
void s21::MapIterator<key_type, mapped_type>::operator--() {
  BinaryTree<key_type, mapped_type>* old_node = current_;
  if (current_->getLeft() != nullptr) {
    goLeft();
    while (current_->getRight() != nullptr) goRight();
  } else {
    while (current_->getParent() != nullptr &&
           current_ == current_->getParent()->getLeft())
      goUp();
    if (current_->getParent() == nullptr)
      current_ = nullptr;
    else
      goUp();
  }
  if (current_ == nullptr) current_ = old_node;
}

template <class key_type, class mapped_type>
void s21::MapIterator<key_type, mapped_type>::goToKey(key_type key) {
  BinaryTree<key_type, mapped_type>* old_node = current_;
  if (current_ != nullptr) {
    goToRoot();
    while (current_ != nullptr && current_->getValue().first != key) {
      current_ = current_->getValue().first > key ? current_->getLeft()
                                                  : current_->getRight();
    }
  }
  if (current_ == nullptr) {
    current_ = old_node;
    throw std::out_of_range("Key was not found");
  }
}

template <class key_type, class mapped_type>
typename s21::MapIterator<key_type, mapped_type>::value_type
s21::MapIterator<key_type, mapped_type>::operator*() const {
  if (getNodePtr() == nullptr) throw std::invalid_argument("Node is nullptr");
  return current_->getValue();
}

template <class key_type, class mapped_type>
s21::BinaryTree<key_type, mapped_type>*
s21::MapIterator<key_type, mapped_type>::getNodePtr() const {
  return current_;
}

template <class key_type, class mapped_type>
void s21::MapIterator<key_type, mapped_type>::goLeft() {
  if (current_->getLeft() != nullptr) current_ = current_->getLeft();
}

template <class key_type, class mapped_type>
void s21::MapIterator<key_type, mapped_type>::goUp() {
  if (current_->getParent() != nullptr) current_ = current_->getParent();
}

template <class key_type, class mapped_type>
void s21::MapIterator<key_type, mapped_type>::goRight() {
  if (current_->getRight() != nullptr) current_ = current_->getRight();
}

/*const iterator*/

template <class key_type, class mapped_type>
s21::MapConstIterator<key_type, mapped_type>::MapConstIterator() {
  current_ = nullptr;
}

template <class key_type, class mapped_type>
s21::MapConstIterator<key_type, mapped_type>::MapConstIterator(
    BinaryTree<key_type, mapped_type>* ptr) {
  current_ = ptr;
}

template <class key_type, class mapped_type>
s21::MapConstIterator<key_type, mapped_type>::~MapConstIterator() {
  current_ = nullptr;
}

template <class key_type, class mapped_type>
void s21::MapConstIterator<key_type, mapped_type>::operator=(
    BinaryTree<key_type, mapped_type>* ptr) {
  current_ = ptr;
}

template <class key_type, class mapped_type>
bool s21::MapConstIterator<key_type, mapped_type>::operator==(
    const MapConstIterator& other) const {
  return current_ == other.getNodePtr();
}

template <class key_type, class mapped_type>
bool s21::MapConstIterator<key_type, mapped_type>::operator!=(
    const MapConstIterator& other) const {
  return current_ != other.getNodePtr();
}

template <class key_type, class mapped_type>
void s21::MapConstIterator<key_type, mapped_type>::goToRoot() {
  while (current_->getParent() != nullptr) current_ = current_->getParent();
}

template <class key_type, class mapped_type>
void s21::MapConstIterator<key_type, mapped_type>::operator++() {
  BinaryTree<key_type, mapped_type>* old_node = current_;
  if (current_->getRight() != nullptr) {
    goRight();
    while (current_->getLeft() != nullptr) goLeft();
  } else {
    while (current_->getParent() != nullptr &&
           current_ == current_->getParent()->getRight())
      goUp();
    if (current_->getParent() == nullptr)
      current_ = nullptr;
    else
      goUp();
  }
  if (current_ == nullptr) current_ = old_node;
}

template <class key_type, class mapped_type>
void s21::MapConstIterator<key_type, mapped_type>::operator--() {
  BinaryTree<key_type, mapped_type>* old_node = current_;
  if (current_->getLeft() != nullptr) {
    goLeft();
    while (current_->getRight() != nullptr) goRight();
  } else {
    while (current_->getParent() != nullptr &&
           current_ == current_->getParent()->getLeft())
      goUp();
    if (current_->getParent() == nullptr)
      current_ = nullptr;
    else
      goUp();
  }
  if (current_ == nullptr) current_ = old_node;
}

template <class key_type, class mapped_type>
void s21::MapConstIterator<key_type, mapped_type>::goToKey(key_type key) {
  BinaryTree<key_type, mapped_type>* old_node = current_;
  goToRoot();
  while (current_ != nullptr && current_->getValue().first != key) {
    current_ = current_->getValue().first > key ? current_->getLeft()
                                                : current_->getRight();
  }
  if (current_ == nullptr) {
    current_ = old_node;
    throw std::out_of_range("Key was not found");
  }
}

template <class key_type, class mapped_type>
const typename s21::MapConstIterator<key_type, mapped_type>::value_type
s21::MapConstIterator<key_type, mapped_type>::operator*() const {
  return current_->getValue();
}

template <class key_type, class mapped_type>
typename s21::map<key_type, mapped_type>::const_iterator
s21::map<key_type, mapped_type>::const_begin() const {
  MapConstIterator iterator(root_);
  if (root_ != nullptr)
    while (iterator.getNodePtr()->getLeft() != nullptr) iterator.goLeft();
  return iterator;
}

template <class key_type, class mapped_type>
typename s21::map<key_type, mapped_type>::const_iterator
s21::map<key_type, mapped_type>::const_end() const {
  MapConstIterator iterator(root_);
  if (root_ != nullptr)
    while (iterator.getNodePtr()->getRight() != nullptr) iterator.goRight();
  return iterator;
}

template <class key_type, class mapped_type>
s21::BinaryTree<key_type, mapped_type>*
s21::MapConstIterator<key_type, mapped_type>::getNodePtr() const {
  return current_;
}

template <class key_type, class mapped_type>
void s21::MapConstIterator<key_type, mapped_type>::goLeft() {
  if (current_->getLeft() != nullptr) current_ = current_->getLeft();
}

template <class key_type, class mapped_type>
void s21::MapConstIterator<key_type, mapped_type>::goUp() {
  if (current_->getParent() != nullptr) current_ = current_->getParent();
}

template <class key_type, class mapped_type>
void s21::MapConstIterator<key_type, mapped_type>::goRight() {
  if (current_->getRight() != nullptr) current_ = current_->getRight();
}

/*map*/
template <class key_type, class mapped_type>
s21::map<key_type, mapped_type>::map() {
  root_ = nullptr;
  size_ = 0;
}

template <class key_type, class mapped_type>
s21::map<key_type, mapped_type>::map(
    std::initializer_list<value_type> const& items) {
  root_ = nullptr;
  size_ = 0;
  for (const auto& item : items) insert(item);
}

template <class key_type, class mapped_type>
s21::map<key_type, mapped_type>::map(const map& m) {
  root_ = nullptr;
  size_ = 0;
  merge(m);
}

template <class key_type, class mapped_type>
s21::map<key_type, mapped_type>::map(map&& m) {
  root_ = nullptr;
  size_ = 0;
  merge(m);
}

template <class key_type, class mapped_type>
s21::map<key_type, mapped_type>::~map() {
  default_destructor();
}

template <class key_type, class mapped_type>
void s21::map<key_type, mapped_type>::default_destructor() {
  destroy_tree();
  root_ = nullptr;
  size_ = 0;
}

template <class key_type, class mapped_type>
s21::BinaryTree<key_type, mapped_type>*
s21::map<key_type, mapped_type>::getRoot() const {
  return root_;
}

template <class key_type, class mapped_type>
s21::map<key_type, mapped_type> s21::map<key_type, mapped_type>::operator=(
    map&& m) {
  if (this != &m) {
    clear();
    merge(m);
  }
  return *this;
}

template <class key_type, class mapped_type>
s21::map<key_type, mapped_type> s21::map<key_type, mapped_type>::operator=(
    const map& m) {
  if (this != &m) {
    clear();
    merge(m);
  }
  return *this;
}

template <class key_type, class mapped_type>
mapped_type& s21::map<key_type, mapped_type>::at(const key_type& key) {
  if (root_ == nullptr) throw std::invalid_argument("Map is not initialized");
  MapIterator iterator = begin();
  iterator.goToKey(key);
  return iterator.getNodePtr()->getValue().second;
}

template <class key_type, class mapped_type>
mapped_type& s21::map<key_type, mapped_type>::operator[](const key_type& key) {
  MapIterator iterator = begin();
  try {
    iterator.goToKey(key);
  } catch (const std::exception& e) {
    std::pair<key_type, mapped_type> value;
    value.first = key;
    insert(value);
    iterator = begin();
    iterator.goToKey(key);
  }
  return iterator.getNodePtr()->getValue().second;
}

template <class key_type, class mapped_type>
typename s21::map<key_type, mapped_type>::iterator
s21::map<key_type, mapped_type>::begin() {
  MapIterator iterator(root_);
  if (root_ != nullptr)
    while (iterator.getNodePtr()->getLeft() != nullptr) iterator.goLeft();
  return iterator;
}

template <class key_type, class mapped_type>
typename s21::map<key_type, mapped_type>::iterator
s21::map<key_type, mapped_type>::end() {
  MapIterator iterator(root_);
  if (root_ != nullptr)
    while (iterator.getNodePtr()->getRight() != nullptr) iterator.goRight();
  return iterator;
}

template <class key_type, class mapped_type>
bool s21::map<key_type, mapped_type>::empty() {
  return size_ == 0;
}

template <class key_type, class mapped_type>
typename s21::map<key_type, mapped_type>::size_type
s21::map<key_type, mapped_type>::size() {
  return size_;
}

template <class key_type, class mapped_type>
typename s21::map<key_type, mapped_type>::size_type
s21::map<key_type, mapped_type>::max_size() {
  return std::numeric_limits<size_type>::max();
}

template <class key_type, class mapped_type>
void s21::map<key_type, mapped_type>::clear() {
  default_destructor();
}

template <class key_type, class mapped_type>
std::pair<typename s21::map<key_type, mapped_type>::iterator, bool>
s21::map<key_type, mapped_type>::default_insert(const value_type& value) {
  std::pair<iterator, bool> result;
  if (root_ == nullptr) {
    size_++;
    BinaryTree<key_type, mapped_type>* new_root =
        new BinaryTree<key_type, mapped_type>;
    new_root->setValue(value);
    root_ = new_root;
    MapIterator<key_type, mapped_type> temp_iterator = begin();
    result.first = temp_iterator;
    result.second = 1;
  } else if (root_->getValue().first == value.first) {
    MapIterator<key_type, mapped_type> temp_iterator = begin();
    temp_iterator.goToRoot();
    result.first = temp_iterator;
    result.second = 0;
  } else {
    MapIterator<key_type, mapped_type> temp_iterator = begin();
    temp_iterator.goToRoot();
    key_type old_key;
    do {
      old_key = (*temp_iterator).first;
      if ((*temp_iterator).first > value.first)
        temp_iterator.goLeft();
      else
        temp_iterator.goRight();
    } while ((*temp_iterator).first != value.first &&
             (*temp_iterator).first != old_key);
    if ((*temp_iterator).first == value.first) {
      result.second = 0;
    } else {
      size_++;
      createNewNode(&(temp_iterator), value);
      if (value.first > (*temp_iterator).first)
        temp_iterator.goRight();
      else
        temp_iterator.goLeft();
      result.second = 1;
    }
    result.first = temp_iterator;
  }
  if (result.second == 1) rebalance_insert(result.first.getNodePtr());
  return result;
}

template <class key_type, class mapped_type>
void s21::map<key_type, mapped_type>::rebalance_erase(
    BinaryTree<key_type, mapped_type>* node) {
  BinaryTree<key_type, mapped_type>* parent = node->getParent();
  BinaryTree<key_type, mapped_type>* brother =
      parent == nullptr
          ? nullptr
          : (node->getValue() > parent->getValue() ? parent->getLeft()
                                                   : parent->getRight());
  if (parent != nullptr && brother != nullptr && brother->getColor() == BLACK &&
      ((brother->getLeft() != nullptr &&
        brother->getLeft()->getColor() == RED) ||
       (brother->getRight() != nullptr &&
        brother->getRight()->getColor() == RED))) {
    brother->setColor(BLACK);
    if (node->getValue() > parent->getValue()) {
      rotate_in_direction(parent, RIGHT);
    } else {
      rotate_in_direction(parent, LEFT);
    }
    brother = node->getValue() > parent->getValue() ? parent->getLeft()
                                                    : parent->getRight();
  }

  if (parent != nullptr && brother != nullptr && brother->getColor() == BLACK &&
      (brother->getLeft() == nullptr ||
       brother->getLeft()->getColor() == BLACK) &&
      (brother->getRight() == nullptr ||
       brother->getRight()->getColor() == BLACK)) {
    brother->setColor(RED);
    if (parent->getColor() == BLACK) {
      rebalance_erase(parent);
    } else {
      parent->setColor(BLACK);
    }
  }

  if (parent != nullptr && brother != nullptr && brother->getColor() == RED) {
    brother->setColor(BLACK);
    parent->setColor(RED);
    if (parent->getLeft() == brother) {
      rotate_in_direction(parent, RIGHT);
    } else {
      rotate_in_direction(parent, LEFT);
    }
    brother = node->getValue() > parent->getValue() ? parent->getLeft()
                                                    : parent->getRight();
  }

  if (parent != nullptr && brother != nullptr && brother->getColor() == BLACK &&
      brother->getRight() != nullptr &&
      brother->getRight()->getColor() == RED &&
      (brother->getLeft() == nullptr ||
       brother->getLeft()->getColor() == BLACK)) {
    brother->setColor(parent->getColor());
    parent->setColor(BLACK);
    brother->getRight()->setColor(BLACK);
    rotate_in_direction(parent, LEFT);
  }
}

template <class key_type, class mapped_type>
void s21::map<key_type, mapped_type>::rebalance_insert(
    BinaryTree<key_type, mapped_type>* newNode) {
  if (newNode->getParent() != nullptr &&
      newNode->getParent()->getColor() == RED) {
    bool isRecolorPerformed = recolor(newNode);
    if (!isRecolorPerformed) rotate(newNode);
  }
}

template <class key_type, class mapped_type>
void s21::map<key_type, mapped_type>::rotate(
    BinaryTree<key_type, mapped_type>* node) {
  BinaryTree<key_type, mapped_type>* parent = node->getParent();
  BinaryTree<key_type, mapped_type>* grandpa =
      parent == nullptr ? nullptr : parent->getParent();
  if (parent != nullptr && grandpa != nullptr) {
    if (parent->getLeft() == node && grandpa->getLeft() == parent) {
      rotate_in_direction(grandpa, RIGHT);
      grandpa->setColor(RED);
      node->setColor(RED);
      parent->setColor(BLACK);
    } else if (parent->getRight() == node && grandpa->getRight() == parent) {
      rotate_in_direction(grandpa, LEFT);
      grandpa->setColor(RED);
      node->setColor(RED);
      parent->setColor(BLACK);
    } else if (parent->getRight() == node && grandpa->getLeft() == parent) {
      rotate_in_direction(parent, LEFT);
      rotate_in_direction(grandpa, RIGHT);
      grandpa->setColor(RED);
      parent->setColor(RED);
      node->setColor(BLACK);
    } else if (parent->getLeft() == node && grandpa->getRight() == parent) {
      rotate_in_direction(parent, RIGHT);
      rotate_in_direction(grandpa, LEFT);
      grandpa->setColor(RED);
      parent->setColor(RED);
      node->setColor(BLACK);
    }
  }
}

template <class key_type, class mapped_type>
void s21::map<key_type, mapped_type>::rotate_in_direction(
    BinaryTree<key_type, mapped_type>* node, bool direction) {
  BinaryTree<key_type, mapped_type>* child =
      direction == RIGHT ? node->getLeft() : node->getRight();
  BinaryTree<key_type, mapped_type>* parent = node->getParent();
  node->setParent(child);
  if (child != nullptr) {
    child->setParent(parent);
    if (parent != nullptr) {
      if (parent->getLeft() == node) {
        parent->setLeft(child);
      } else {
        parent->setRight(child);
      }
    } else {
      root_ = child;
    }

    if (direction == RIGHT) {
      node->setLeft(child->getRight());
      if (child->getRight() != nullptr) child->getRight()->setParent(node);
      child->setRight(node);
    } else {
      node->setRight(child->getLeft());
      if (child->getLeft() != nullptr) child->getLeft()->setParent(node);
      child->setLeft(node);
    }
  }
}

template <class key_type, class mapped_type>
bool s21::map<key_type, mapped_type>::recolor(
    BinaryTree<key_type, mapped_type>* node) {
  bool result = false;
  BinaryTree<key_type, mapped_type>* parent = node->getParent();
  BinaryTree<key_type, mapped_type>* grandpa =
      parent == nullptr ? nullptr : parent->getParent();
  BinaryTree<key_type, mapped_type>* uncle =
      grandpa == nullptr ? nullptr
                         : (grandpa->getLeft() == parent ? grandpa->getRight()
                                                         : grandpa->getLeft());
  if (uncle != nullptr && uncle->getColor() == RED) {
    parent->setColor(BLACK);
    uncle->setColor(BLACK);
    if (grandpa->getParent() != nullptr) grandpa->setColor(RED);
    if (grandpa->getParent() != nullptr &&
        grandpa->getParent()->getColor() == RED)
      rebalance_insert(grandpa);
    result = true;
  }
  return result;
}

template <class key_type, class mapped_type>
void s21::map<key_type, mapped_type>::createNewNode(
    s21::map<key_type, mapped_type>::iterator* iter,
    std::pair<key_type, mapped_type> value) {
  if ((**iter).first > value.first) {
    BinaryTree<key_type, mapped_type>* leftNode =
        new BinaryTree<key_type, mapped_type>;
    leftNode->setValue(value);
    iter->getNodePtr()->setLeft(leftNode);
    leftNode->setParent(iter->getNodePtr());
  } else {
    BinaryTree<key_type, mapped_type>* rightNode =
        new BinaryTree<key_type, mapped_type>;
    rightNode->setValue(value);
    iter->getNodePtr()->setRight(rightNode);
    rightNode->setParent(iter->getNodePtr());
  }
}

template <class key_type, class mapped_type>
std::pair<typename s21::map<key_type, mapped_type>::iterator, bool>
s21::map<key_type, mapped_type>::insert(const value_type& value) {
  return default_insert(value);
}

template <class key_type, class mapped_type>
std::pair<typename s21::map<key_type, mapped_type>::iterator, bool>
s21::map<key_type, mapped_type>::insert(const key_type& key,
                                        const mapped_type& obj) {
  std::pair<key_type, mapped_type> value;
  value.first = key;
  value.second = obj;
  return default_insert(value);
}

template <class key_type, class mapped_type>
std::pair<typename s21::map<key_type, mapped_type>::iterator, bool>
s21::map<key_type, mapped_type>::insert_or_assign(const key_type& key,
                                                  const mapped_type& obj) {
  std::pair<key_type, mapped_type> value;
  value.first = key;
  value.second = obj;
  std::pair<iterator, bool> result = default_insert(value);
  if (result.second == 0) {
    at(key) = obj;
    result.second = 1;
  }
  return result;
}

template <class key_type, class mapped_type>
void s21::map<key_type, mapped_type>::erase(
    s21::map<key_type, mapped_type>::iterator pos) {
  if (contains((*pos).first)) {
    size_--;
    BinaryTree<key_type, mapped_type>* nodeToDelete = pos.getNodePtr();
    char numberOfChilds = (nodeToDelete->getRight() != nullptr) +
                          (nodeToDelete->getLeft() != nullptr);
    BinaryTree<key_type, mapped_type>* replacingNode = nullptr;
    switch (numberOfChilds) {
      case 0:
        if (nodeToDelete->getParent() != nullptr) {
          if (nodeToDelete->getParent()->getLeft() == nodeToDelete)
            nodeToDelete->getParent()->setLeft(nullptr);
          else
            nodeToDelete->getParent()->setRight(nullptr);
        }
        break;
      case 1:
        replacingNode = nodeToDelete->getLeft() != nullptr
                            ? nodeToDelete->getLeft()
                            : nodeToDelete->getRight();
        if (nodeToDelete->getParent() != nullptr) {
          if (nodeToDelete->getParent()->getLeft() == nodeToDelete)
            nodeToDelete->getParent()->setLeft(replacingNode);
          else
            nodeToDelete->getParent()->setRight(replacingNode);
        }
        if (nodeToDelete->getLeft() != nullptr)
          nodeToDelete->getLeft()->setParent(nodeToDelete->getParent());
        else
          nodeToDelete->getRight()->setParent(nodeToDelete->getParent());
        break;
      case 2:
        eraseIfHaveBothChildrenInErase(replacingNode, nodeToDelete);
        break;
    }
    if (nodeToDelete->getParent() == nullptr) root_ = replacingNode;
    rebalance_erase(nodeToDelete);
    delete nodeToDelete;
    pos = begin();
  } else {
    throw std::out_of_range("Key was not found");
  }
}

template <class key_type, class mapped_type>
void s21::map<key_type, mapped_type>::swap(
    s21::map<key_type, mapped_type>& other) {
  map<key_type, mapped_type> temp_map = *this;
  *this = other;
  other = temp_map;
}
template <class key_type, class mapped_type>
void s21::map<key_type, mapped_type>::merge(
    const s21::map<key_type, mapped_type>& other) {
  if (other.getRoot() != root_) {
    MapConstIterator begin = other.const_begin();
    MapConstIterator end = other.const_end();
    while (begin != end) {
      insert(*begin);
      ++begin;
    }
    if (end.getNodePtr() != nullptr) insert(*end);
  }
}

template <class key_type, class mapped_type>
bool s21::map<key_type, mapped_type>::contains(const key_type& key) {
  MapIterator iterator = begin();
  MapIterator iterator_end = end();
  bool result = 0;
  while (iterator != iterator_end && result == 0) {
    result = (*iterator).first == key;
    ++iterator;
  }
  if (result == 0 && iterator_end.getNodePtr() != nullptr)
    result = (*iterator_end).first == key;
  return result;
}

template <class key_type, class mapped_type>
void s21::map<key_type, mapped_type>::destroy_tree() {
  MapIterator iterator = begin();
  MapIterator iterator_end = end();
  while (iterator != iterator_end) {
    erase(iterator);
    iterator = begin();
  }
  if (iterator_end.getNodePtr() != nullptr) erase(iterator_end);
}

template <class key_type, class mapped_type>
template <typename... Args>
std::vector<std::pair<typename s21::map<key_type, mapped_type>::iterator, bool>>
s21::map<key_type, mapped_type>::insert_many(Args&&... args) {
  std::vector<std::pair<iterator, bool>> result = {
      (insert(std::forward<Args>(args)))...};
  return result;
}

template <class key_type, class mapped_type>
void s21::map<key_type, mapped_type>::eraseIfHaveBothChildrenInErase(
    BinaryTree<key_type, mapped_type>*& replacingNode,
    BinaryTree<key_type, mapped_type>* nodeToDelete) {
  replacingNode = nodeToDelete->getRight();
  while (replacingNode->getLeft() != nullptr) {
    replacingNode = replacingNode->getLeft();
  }
  if (replacingNode->getRight() != nullptr &&
      replacingNode->getParent() != nodeToDelete) {
    replacingNode->getParent()->setLeft(replacingNode->getRight());
    replacingNode->getRight()->setParent(replacingNode->getParent());
  } else if (replacingNode->getParent() != nodeToDelete) {
    replacingNode->getParent()->setLeft(nullptr);
  }
  if (replacingNode != nodeToDelete->getLeft()) {
    replacingNode->setLeft(nodeToDelete->getLeft());
    if (nodeToDelete->getLeft() != nullptr) {
      nodeToDelete->getLeft()->setParent(replacingNode);
    }
  }
  if (nodeToDelete->getRight() != replacingNode) {
    replacingNode->setRight(nodeToDelete->getRight());
    if (nodeToDelete->getRight() != nullptr) {
      nodeToDelete->getRight()->setParent(replacingNode);
    }
  }
  replacingNode->setParent(nodeToDelete->getParent());
  if (nodeToDelete->getParent() != nullptr) {
    if (nodeToDelete->getParent()->getLeft() == nodeToDelete) {
      nodeToDelete->getParent()->setLeft(replacingNode);
    } else {
      nodeToDelete->getParent()->setRight(replacingNode);
    }
  }
}