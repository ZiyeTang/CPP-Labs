#include "branched-linked-list.hpp"

BLL::BLL() { head_ = nullptr; }

void BLL::Copy(const BLL& to_copy, Node*& head) {
  Node* copy_cur = to_copy.head_;

  if (copy_cur == nullptr) {
    return;
  }

  head = new Node(copy_cur->data_);
  if (copy_cur->next_bll_ != nullptr) {
    head->next_bll_ = new BLL();
    Copy(*(copy_cur->next_bll_), head->next_bll_->head_);
  }

  Node* cur = head;
  copy_cur = copy_cur->next_node_;

  while (copy_cur != nullptr) {
    cur->next_node_ = new Node(copy_cur->data_);

    if (copy_cur->next_bll_ != nullptr) {
      cur->next_node_->next_bll_ = new BLL();
      Copy(*(copy_cur->next_bll_), cur->next_node_->next_bll_->head_);
    }
    cur = cur->next_node_;
    copy_cur = copy_cur->next_node_;
  }
}

void BLL::Destroy() {
  Node* cur = head_;
  while (cur != nullptr) {
    if (cur->next_bll_ != nullptr) {
      delete cur->next_bll_;
      Node* temp = cur->next_node_;
      delete cur;
      cur = temp;
      continue;
    }
    Node* temp = cur->next_node_;
    delete cur;
    cur = temp;
  }
}

BLL::BLL(const BLL& to_copy) {
  head_ = nullptr;
  Copy(to_copy, head_);
}

BLL::~BLL() {
  Destroy();
  head_ = nullptr;
}

BLL& BLL::operator=(const BLL& rhs) {
  if (this == &rhs) {
    return *this;
  }

  Destroy();
  head_ = nullptr;
  Copy(rhs, head_);
  return *this;
}

Node* BLL::PushBack(char dat) {
  Node* new_node = new Node(dat);
  if (head_ == nullptr) {
    head_ = new_node;
    return new_node;
  }

  Node* cur = head_;
  while (cur->next_node_ != nullptr) {
    cur = cur->next_node_;
  }
  cur->next_node_ = new_node;
  return new_node;
}

Node* BLL::GetNodeAt(size_t& idx, Node* head) const {
  Node* cur = head;
  while (cur != nullptr) {
    if (idx == 0) {
      return cur;
    }

    idx--;
    if (cur->next_bll_ != nullptr) {
      Node* res = GetNodeAt(idx, cur->next_bll_->head_);
      if (idx == 0) {
        return res;
      }
    }
    cur = cur->next_node_;
  }

  return nullptr;
}

char BLL::GetAt(size_t idx) const {
  Node* node = GetNodeAt(idx, head_);
  if (node == nullptr) {
    throw std::invalid_argument("index out of bound");
  }
  return node->data_;
}

void BLL::SetAt(size_t idx, char dat) {
  Node* node = GetNodeAt(idx, head_);
  if (node == nullptr) {
    throw std::invalid_argument("index out of bound");
  }
  node->data_ = dat;
}

size_t BLL::SizeHelper(const BLL* bll) const {
  if (bll == nullptr) {
    return 0;
  }

  Node* cur = bll->head_;
  size_t size = 0;
  while (cur != nullptr) {
    size += 1 + SizeHelper(cur->next_bll_);
    cur = cur->next_node_;
  }
  return size;
}

size_t BLL::Size() const { return SizeHelper(this); }

std::string BLL::ToStringHelper(const BLL* bll) const {
  if (bll == nullptr) {
    return "";
  }

  Node* cur = bll->head_;
  std::string str;
  while (cur != nullptr) {
    str += cur->data_ + ToStringHelper(cur->next_bll_);
    cur = cur->next_node_;
  }
  return str;
}

std::string BLL::ToString() const { return ToStringHelper(this); }

bool BLL::IsBLLAcyclic() const { return false; }

void BLL::Join(size_t idx, BLL* list) {
  Node* node = GetNodeAt(idx, head_);
  if (node == nullptr || node->next_bll_ != nullptr) {
    throw std::invalid_argument("index out of bound");
  }

  node->next_bll_ = list;

  if (!IsBLLAcyclic()) {
    node->next_bll_ = nullptr;
    throw std::invalid_argument("invalid list");
  }
}
