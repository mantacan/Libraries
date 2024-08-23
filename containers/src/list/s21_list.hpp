
/* DEFAULT */
template <typename T>
list<T>::list() noexcept : head(nullptr), size_(0) {}

/* CREATED LIST IN SIZE "N" */
template <typename T>
list<T>::list(size_t n) : head(nullptr), size_(0) {
  for (size_t i = 0; i < n; ++i) {
    push_back(T());
  }
}

/* INIT LIST*/
template <typename T>
list<T>::list(std::initializer_list<T> const &items) : head(nullptr), size_(0) {
  for (const auto &item : items) {
    push_back(item);
  }
}

/* COPY LIST */
template <typename T>
list<T>::list(const list &l) : head(nullptr), size_(0) {
  for (const auto &item : l) {
    push_back(item);
  }
}

/* MOVE DATA LIST */
template <typename T>
list<T>::list(list &&l) noexcept : head(l.head), size_(l.size_) {
  l.head = nullptr;
  l.size_ = 0;
}

/* DECONSTRUCT */
template <typename T>
list<T>::~list() noexcept {
  clear();
}

/*
 *
 *
 *
 *
 *
 *
 *    CLASS LIST : OVERLOADED OPERATORS
 *
 *
 *
 *
 *
 *
 */

template <typename T>
list<T> &list<T>::operator=(list &&l) noexcept {
  if (this != &l) {
    clear();
    head = l.head;
    size_ = l.size_;
    l.head = nullptr;
    l.size_ = 0;
  }
  return *this;
}

/*
 *
 *
 *
 *
 *
 *
 *    CLASS LIST : GETS AND SETS
 *
 *
 *
 *
 *
 *
 */
template <typename T>
typename list<T>::Node *list<T>::getHead() const {
  return head;
}

template <typename T>
void list<T>::setHead(Node *newHead) {
  head = newHead;
}

template <typename T>
typename list<T>::size_type list<T>::getSize() const {
  return size_;
}

template <typename T>
void list<T>::setSize(size_type newSize) {
  size_ = newSize;
}
template <typename T>
typename list<T>::Node *list<T>::getNext(Node *node) const {
  return node->next;
}

template <typename T>
void list<T>::setNext(Node *node, Node *nextNode) {
  node->next = nextNode;
}

template <typename T>
typename list<T>::Node *list<T>::getPrev(Node *node) const {
  return node->prev;
}

template <typename T>
void list<T>::setPrev(Node *node, Node *prevNode) {
  node->prev = prevNode;
}

/*
 *
 *
 *
 *
 *
 *
 *    CLASS LIST : METHODS
 *
 *
 *
 *
 *
 *
 */

template <typename T>
void list<T>::clear() noexcept {
  while (head) {
    Node *temp = head->next;
    delete head;
    head = temp;
  }

  size_ = 0;
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  if (pos.getCurrent() == nullptr) {
    throw std::invalid_argument("Invalid iterator position");
  }

  Node *newNode = new (std::nothrow) Node(value);
  if (newNode == nullptr) {
    // Обработка ошибки: не удалось выделить память для нового узла
    throw std::bad_alloc();
  }

  newNode->prev = pos.getCurrent()->prev;
  newNode->next = pos.getCurrent();
  if (pos.getCurrent()->prev) {
    pos.getCurrent()->prev->next = newNode;
  } else {
    head = newNode;
  }
  pos.getCurrent()->prev = newNode;
  ++size_;
  return iterator(newNode);
}

template <typename T>
void list<T>::erase(iterator pos) {
  if (pos == end()) {
    return;
  }

  Node *current = pos.getCurrent();

  if (current->prev) {
    current->prev->next = current->next;
  } else {
    head = current->next;
  }

  if (current->next) {
    current->next->prev = current->prev;
  }

  delete current;
  --size_;
}

template <typename T>
void list<T>::push_back(const_reference value) {
  Node *newNode = new Node(value);
  if (!head) {
    head = newNode;
  } else {
    Node *current = head;
    while (current->next) {
      current = current->next;
    }
    current->next = newNode;
    newNode->prev = current;
  }
  ++size_;
}

template <typename T>
void list<T>::push_front(const_reference value) {
  Node *newNode = new Node(value);
  if (!head) {
    head = newNode;
  } else {
    newNode->next = head;
    head->prev = newNode;
    head = newNode;
  }
  ++size_;
}

template <typename T>
void list<T>::pop_back() {
  if (!head) return;

  if (!head->next) {
    delete head;
    head = nullptr;
  } else {
    Node *current = head;
    while (current->next->next) {
      current = current->next;
    }
    delete current->next;
    current->next = nullptr;
  }
  --size_;
}

template <typename T>
void list<T>::pop_front() {
  if (!head) return;

  Node *temp = head;
  head = head->next;
  delete temp;
  if (head) head->prev = nullptr;
  --size_;
}

template <typename T>
void list<T>::swap(list &other) {
  std::swap(head, other.head);
  std::swap(size_, other.size_);
}

template <typename T>
void list<T>::merge(list &other) {
  Node *temp1 = head;
  Node *temp2 = other.head;

  list<T> result;

  while (temp1 != nullptr && temp2 != nullptr) {
    if (temp1->data < temp2->data) {
      result.push_back(temp1->data);
      temp1 = temp1->next;
    } else {
      result.push_back(temp2->data);
      temp2 = temp2->next;
    }
  }

  while (temp1 != nullptr) {
    result.push_back(temp1->data);
    temp1 = temp1->next;
  }

  while (temp2 != nullptr) {
    result.push_back(temp2->data);
    temp2 = temp2->next;
  }

  swap(result);
}

template <typename T>
void list<T>::splice(const_iterator pos, list &other) {
  if (!other.empty()) {
    Node *posNode = pos.getCurrent();

    if (posNode == nullptr) {
      if (head == nullptr) {
        head = other.head;
      } else {
        Node *lastNode = head;
        while (lastNode->next != nullptr) {
          lastNode = lastNode->next;
        }
        lastNode->next = other.head;
        other.head->prev = lastNode;
      }
    } else {
      if (posNode == head) {
        other.tail()->next = head;
        head->prev = other.tail();
        head = other.head;
      } else {
        Node *prevNode = posNode->prev;
        prevNode->next = other.head;
        other.head->prev = prevNode;

        other.tail()->next = posNode;
        posNode->prev = other.tail();
      }
    }

    size_ += other.size();

    other.head = nullptr;
    other.size_ = 0;
  }
}

template <typename T>
typename list<T>::Node *list<T>::tail() const {
  Node *tailNode = head;
  if (tailNode != nullptr) {
    while (tailNode->next != nullptr) {
      tailNode = tailNode->next;
    }
  }
  return tailNode;
}

template <typename T>
void list<T>::reverse() {
  if (head == nullptr || head->next == nullptr) return;

  Node *current = head;
  Node *prev = nullptr;
  Node *next = nullptr;

  while (current != nullptr) {
    next = current->next;
    current->next = prev;
    current->prev = next;

    prev = current;
    current = next;
  }

  head = prev;
}

template <typename T>
void list<T>::unique() {
  if (head == nullptr || head->next == nullptr) return;

  Node *current = head;
  size_type new_size = 1;

  while (current->next != nullptr) {
    if (current->data == current->next->data) {
      Node *to_delete = current->next;
      current->next = to_delete->next;
      if (to_delete->next != nullptr) {
        to_delete->next->prev = current;
      }
      delete to_delete;
    } else {
      current = current->next;
      ++new_size;
    }
  }
  size_ = new_size;
}

template <typename T>
void list<T>::sort() {
  if (size_ <= 1) return;

  bool swapped;
  Node *prev = nullptr;

  do {
    swapped = false;
    Node *current = head;

    while (current != nullptr && current->next != nullptr) {
      if (current->data > current->next->data) {
        if (prev == nullptr) {
          head = current->next;
        } else {
          prev->next = current->next;
        }

        Node *temp = current->next->next;
        current->next->next = current;
        current->next = temp;

        prev = prev == nullptr ? head : prev->next;
        swapped = true;
      } else {
        prev = current;
        current = current->next;
      }
    }
  } while (swapped);
}

template <typename T>
typename s21::list<T>::const_reference list<T>::front() const {
  if (this->empty()) {
    throw std::out_of_range("List is empty");
  }
  return this->getHead()->data;
}

template <typename T>
typename s21::list<T>::const_reference list<T>::back() const {
  if (this->empty()) {
    throw std::out_of_range("List is empty");
  }

  Node *current = this->getHead();
  while (current->next != nullptr) {
    current = current->next;
  }

  return current->data;
}

/*
 *
 *
 *
 *
 *
 *
 *    CLASS ITERATOR : METHODS
 *
 *
 *
 *
 *
 *
 */

template <typename T>
bool list<T>::ListIterator::operator==(const ListIterator &other) const {
  return current == other.current;
}

template <typename T>
bool list<T>::ListIterator::operator!=(const ListIterator &other) const {
  return !(*this == other);
}

template <typename T>
typename list<T>::ListIterator &list<T>::ListIterator::operator++() {
  if (current) {
    current = current->next;
  }
  return *this;
}

template <typename T>
typename list<T>::ListIterator list<T>::ListIterator::operator++(int) {
  ListIterator temp = *this;
  ++(*this);
  return temp;
}

template <typename T>
typename list<T>::ListIterator::reference list<T>::ListIterator::operator*()
    const {
  return current->data;
}

template <typename T>
typename list<T>::Node *list<T>::ListIterator::getCurrent() const {
  return current;
}

template <typename T>
typename list<T>::Node *list<T>::ListIterator::getNext() const {
  return current->next;
}

template <typename T>
typename list<T>::Node *list<T>::ListIterator::getPrev() const {
  return current->prev;
}
