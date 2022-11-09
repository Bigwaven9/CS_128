#include "dna_strand.hpp"

#include <stdexcept>

DNAstrand::~DNAstrand() {
  Node* temp = head_;
  while (head_ != nullptr) {
    head_ = head_->next;
    delete temp;
    temp = head_;
  }
}

int DNAstrand::Strlen(const char* pattern) {
  int cnt = 0;
  while (pattern[cnt] != '\0') cnt++;
  return cnt;
}

int DNAstrand::Strlen(const DNAstrand& to_splice_in) {
  int cnt = 0;
  Node* temp = to_splice_in.head_;
  while (temp != nullptr) temp = temp->next, cnt++;
  return cnt;
}

void DNAstrand::Remove(int idx, int len) {
  if (idx == 0) {
    Node *cur = head_, *temp = nullptr;
    while (len-- != 0) {
      temp = cur;
      cur = cur->next;
      delete temp;
    }
    head_ = cur;
  } else {
    Node *cur = head_, *temp = nullptr;
    while (--idx != 0) cur = cur->next;
    while (len-- != 0) {
      temp = cur->next;
      cur->next = cur->next->next;
      delete temp;
    }
  }
}

void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
  if (&to_splice_in == this) return;
  if (*pattern == '\0' || to_splice_in.head_ == nullptr) return;
  int s1 = Strlen(pattern), s2 = Strlen(*this);
  int idx = -1;
  Node* temp = head_;
  for (int i = 0; i < s2 - s1 + 1; ++i, temp = temp->next) {
    bool success = true;
    Node* t = temp;
    for (int j = 0; j < s1; ++j, t = t->next) {
      if (t->data != pattern[j]) success = false;
    }
    if (success) idx = i;
  }
  if (idx == -1) throw std::invalid_argument("not find to replace");
  Remove(idx, s1);

  if (idx == 0) {
    to_splice_in.tail_->next = head_;
    head_ = to_splice_in.head_;
  } else {
    Node* cur = head_;
    while (--idx != 0) cur = cur->next;
    to_splice_in.tail_->next = cur->next;
    cur->next = to_splice_in.head_;
  }
  to_splice_in.head_ = to_splice_in.tail_ = nullptr;

  tail_ = head_;
  while (tail_->next != nullptr) tail_ = tail_->next;
}