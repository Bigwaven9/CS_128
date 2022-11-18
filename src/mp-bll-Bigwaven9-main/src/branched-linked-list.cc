#include "branched-linked-list.hpp"

BLL::BLL(const BLL& to_copy) {
  if (to_copy.head_ == nullptr)
    head_ = nullptr;
  else {
    head_ = new Node(to_copy.head_->data_);
    Node *cur = head_, *temp = to_copy.head_;
    while (temp != nullptr) {
      if (temp->next_bll_ != nullptr)
        cur->next_bll_ = new BLL(*temp->next_bll_);
      if (temp->next_node_ != nullptr)
        cur->next_node_ = new Node(temp->next_node_->data_);
      cur = cur->next_node_;
      temp = temp->next_node_;
    }
  }
}

BLL::~BLL() {
  Clear(head_);
  head_ = nullptr;
}

void BLL::Clear(Node* cur) {
  if (cur == nullptr) return;
  delete cur->next_bll_;
  Clear(cur->next_node_);
  delete cur;
}

BLL& BLL::operator=(const BLL& rhs) {
  if (this == &rhs) return *this;
  Clear(head_);
  if (rhs.head_ == nullptr)
    head_ = nullptr;
  else {
    head_ = new Node(rhs.head_->data_);
    Node *cur = head_, *temp = rhs.head_;
    while (temp != nullptr) {
      if (temp->next_bll_ != nullptr)
        cur->next_bll_ = new BLL(*temp->next_bll_);
      if (temp->next_node_ != nullptr)
        cur->next_node_ = new Node(temp->next_node_->data_);
      cur = cur->next_node_;
      temp = temp->next_node_;
    }
  }
  return *this;
}

Node* BLL::PushBack(char dat) {
  Node* temp = new Node(dat);
  if (head_ == nullptr)
    head_ = temp;
  else {
    Node* cur = head_;
    while (cur->next_node_ != nullptr) cur = cur->next_node_;
    cur->next_node_ = temp;
  }
  return temp;
}

char BLL::GetAt(size_t idx) const {
  Node* cur = head_;
  while (idx != 0 && Next(cur) != nullptr) cur = Next(cur), idx--;
  if (idx != 0) throw std::invalid_argument("");
  return cur->data_;
}

void BLL::SetAt(size_t idx, char dat) {
  Node* cur = head_;
  while (idx != 0 && Next(cur) != nullptr) cur = Next(cur), idx--;
  if (idx != 0) throw std::invalid_argument("");
  cur->data_ = dat;
}

void BLL::Join(size_t idx, BLL* list) {
  Node* cur = head_;
  while (idx != 0 && Next(cur) != nullptr) cur = Next(cur), idx--;
  if (idx != 0) throw std::invalid_argument("");
  if (cur->next_bll_ != nullptr) throw std::invalid_argument("");
  cur->next_bll_ = list;
  if (!IsBLLAcyclic()) throw std::invalid_argument("");
}

std::string BLL::ToString() const {
  std::string ans;
  Node* cur = head_;
  while (cur != nullptr) {
    ans += cur->data_;
    if (cur->next_bll_ != nullptr) ans += cur->next_bll_->ToString();
    cur = cur->next_node_;
  }
  return ans;
}

size_t BLL::Size() const {
  size_t cnt = 0;
  Node* cur = head_;
  while (cur != nullptr) {
    cnt += (cur->next_bll_ != nullptr ? cur->next_bll_->Size() : 0) + 1;
    cur = cur->next_node_;
  }
  return cnt;
}

bool BLL::IsBLLAcyclic() const {
  Node *slow = head_, *fast = head_;
  while (fast != nullptr && Next(fast) != nullptr) {
    fast = Next(Next(fast));
    slow = Next(slow);
    if (fast == slow) return false;
  }
  return true;
}

Node* BLL::Next(Node* cur) const {
  if (cur->next_bll_ != nullptr)
    return cur->next_bll_->head_;
  else if (cur->next_node_ != nullptr)
    return cur->next_node_;
  return nullptr;
}