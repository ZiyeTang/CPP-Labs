#ifndef CIRCULAR_LINKED_LIST_HPP
#define CIRCULAR_LINKED_LIST_HPP

#include <iostream>

#include "node.hpp"

enum class Order { kASC, kDESC };

template <typename T>
class CircularLinkedList {
public:
  CircularLinkedList() = default;
  CircularLinkedList(const CircularLinkedList<T>& source);
  CircularLinkedList<T>& operator=(const CircularLinkedList<T>& source);
  ~CircularLinkedList();

  void InsertInOrder(const T& data);
  void Reverse();

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os,
                                  const CircularLinkedList<U>& cll);

private:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  Order node_order_ = Order::kASC;
  void Copy(const CircularLinkedList<T>& source);
  void Destruct();
  void InsertAsc(const T& data);
  void InsertDesc(const T& data);
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const CircularLinkedList<T>& cll) {
  Node<T>* iter = cll.head_;
  // empty list condition
  if (iter == nullptr) {
    os << "Empty list";
    return os;
  }
  // non-empty list condition
  do {
    os << iter->data << '\t';
    iter = iter->next;
  } while (iter != cll.head_);

  return os;
}

template <typename T>
CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList<T>& source) {
  Copy(source);
}

template <typename T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(
    const CircularLinkedList<T>& source) {
  if (this == &source) {
    return *this;
  }
  Destruct();
  Copy(source);
  return *this;
}

template <typename T>
CircularLinkedList<T>::~CircularLinkedList() {
  Destruct();
}

template <typename T>
void CircularLinkedList<T>::Copy(const CircularLinkedList<T>& source) {
  node_order_ = source.node_order_;

  if (source.head_ == nullptr) {
    return;
  }

  head_ = new Node<T>(source.head_->data);
  Node<T>* cur = head_;
  Node<T>* cur_s = source.head_->next;
  while (cur_s != source.head_) {
    cur->next = new Node<T>(cur_s->data);
    cur = cur->next;
    cur_s = cur_s->next;
  }
  tail_ = cur;
  tail_->next = head_;
}

template <typename T>
void CircularLinkedList<T>::Destruct() {
  if (head_ == nullptr) {
    return;
  }

  Node<T>* cur = head_;
  while (cur != tail_) {
    Node<T>* temp = cur->next;
    delete cur;
    cur = temp;
  }
  delete cur;
  head_ = nullptr;
  tail_ = nullptr;
}

template <typename T>
void CircularLinkedList<T>::InsertInOrder(const T& data) {
  if (head_ == nullptr) {
    head_ = new Node<T>(data);
    tail_ = head_;
    head_->next = head_;
    return;
  }

  if (node_order_ == Order::kASC) {
    InsertAsc(data);
    return;
  }

  InsertDesc(data);
}

template <typename T>
void CircularLinkedList<T>::InsertAsc(const T& data) {
  Node<T>* prev = tail_;
  Node<T>* cur = head_;
  while (cur != tail_) {
    if (data <= cur->data) {
      auto new_node = new Node<T>(data, cur);
      prev->next = new_node;
      if (cur == head_) {
        head_ = new_node;
      }
      return;
    }
    prev = cur;
    cur = cur->next;
  }

  if (data <= cur->data) {
    auto new_node = new Node<T>(data, cur);
    prev->next = new_node;
    if (head_->data >= data) {
      head_ = new_node;
    }
    return;
  }

  auto new_node = new Node<T>(data, head_);
  tail_->next = new_node;
  tail_ = new_node;
}

template <typename T>
void CircularLinkedList<T>::InsertDesc(const T& data) {
  Node<T>* prev = tail_;
  Node<T>* cur = head_;
  while (cur != tail_) {
    if (data >= cur->data) {
      auto new_node = new Node<T>(data, cur);
      prev->next = new_node;
      if (cur == head_) {
        head_ = new_node;
      }
      return;
    }
    prev = cur;
    cur = cur->next;
  }

  if (data >= cur->data) {
    auto new_node = new Node<T>(data, cur);
    prev->next = new_node;
    if (head_->data <= data) {
      head_ = new_node;
    }
    return;
  }

  auto new_node = new Node<T>(data, head_);
  tail_->next = new_node;
  tail_ = new_node;
}

template <typename T>
void CircularLinkedList<T>::Reverse() {
  if (head_ != tail_) {
    Node<T>* prev = tail_;
    Node<T>* cur = head_;
    while (cur != tail_) {
      Node<T>* next_cur = cur->next;
      cur->next = prev;
      prev = cur;
      cur = next_cur;
    }
    cur->next = prev;
  }
  Node<T>* temp = head_;
  head_ = tail_;
  tail_ = temp;

  if (node_order_ == Order::kASC) {
    node_order_ = Order::kDESC;
    return;
  }

  node_order_ = Order::kASC;
}

#endif