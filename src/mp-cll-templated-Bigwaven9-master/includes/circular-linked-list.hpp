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
  node_order_ = source.node_order_;
  if (source.head_ == nullptr) {
    head_ = tail_ = nullptr;
  } else {
    head_ = new Node<T>(source.head_->data);
    Node<T>*temp = source.head_, *cur = head_;
    source.tail_->next = nullptr;
    while (temp->next != nullptr) {
      temp = temp->next;
      cur->next = new Node<T>(temp->data);
      cur = cur->next;
    }
    tail_ = cur;
    tail_->next = head_;
    source.tail_->next = source.head_;
  }
}

template <typename T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(
    const CircularLinkedList<T>& source) {
  if (this == &source) return *this;
  this->~CircularLinkedList();
  if (this == &source) return *this;
  node_order_ = source.node_order_;
  if (source.head_ == nullptr) {
    head_ = tail_ = nullptr;
  } else {
    head_ = new Node<T>(source.head_->data);
    Node<T>*temp = source.head_, *cur = head_;
    source.tail_->next = nullptr;
    while (temp->next != nullptr) {
      temp = temp->next;
      cur->next = new Node<T>(temp->data);
      cur = cur->next;
    }
    tail_ = cur;
    tail_->next = head_;
    source.tail_->next = source.head_;
  }
  return *this;
}

template <typename T>
CircularLinkedList<T>::~CircularLinkedList() {
  node_order_ = Order::kASC;
  while (head_ != nullptr && head_ != tail_) {
    Node<T>* temp = head_->next;
    delete head_;
    head_ = temp;
  }
  delete tail_;
  head_ = tail_ = nullptr;
}

template <typename T>
void CircularLinkedList<T>::InsertInOrder(const T& data) {
  if (head_ == nullptr) {
    head_ = tail_ = new Node<T>(data);
    tail_->next = head_;
    return;
  }
  bool st = node_order_ == Order::kASC;
  if (st) {
    if (data <= head_->data) {
      head_ = new Node<T>(data, head_);
      tail_->next = head_;
    } else if (data >= tail_->data) {
      tail_->next = new Node<T>(data, head_);
      tail_ = tail_->next;
    } else {
      Node<T>* cur = head_;
      while (cur->next->data < data) cur = cur->next;
      cur->next = new Node<T>(data, cur->next);
    }
  } else {
    if (data >= head_->data) {
      head_ = new Node<T>(data, head_);
      tail_->next = head_;
    } else if (data <= tail_->data) {
      tail_->next = new Node<T>(data, head_);
      tail_ = tail_->next;
    } else {
      Node<T>* cur = head_;
      while (cur->next->data > data) cur = cur->next;
      cur->next = new Node<T>(data, cur->next);
    }
  }
}

template <typename T>
void CircularLinkedList<T>::Reverse() {
  node_order_ = node_order_ == Order::kASC ? Order::kDESC : Order::kASC;
  if (head_ != nullptr) {
    tail_->next = nullptr;
    Node<T>*cur = head_, *pre = nullptr;
    while (cur != nullptr) {
      Node<T>* temp = cur->next;
      cur->next = pre;
      pre = cur;
      cur = temp;
    }
    tail_ = head_;
    head_ = pre;
    tail_->next = head_;
  }
}

#endif