#include "dna_strand.hpp"

#include <stdexcept>

DNAstrand::~DNAstrand() {
  while (head_ != nullptr) {
    Node* temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = nullptr;
}

void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
  if (to_splice_in.head_ == nullptr || pattern == nullptr || *pattern == '\0' ||
      this == &to_splice_in) {
    return;
  }

  Node* start = head_;
  Node* headtmp = nullptr;
  Node* tailtmp = nullptr;

  Node* prev = nullptr;
  bool found = false;
  while (start != nullptr) {
    Node* cur = start;

    int i = 0;
    while (cur != nullptr && pattern[i] != '\0') {
      if (cur->data != pattern[i]) {
        break;
      }
      cur = cur->next;
      i++;
    }

    if (pattern[i] == '\0') {
      headtmp = prev;
      tailtmp = cur;
      found = true;
    }
    prev = start;
    start = start->next;
  }

  if (!found) {
    throw std::invalid_argument("invalid pattern");
  }

  Insert(headtmp, tailtmp, to_splice_in);
}

void DNAstrand::Insert(Node* headtmp, Node* tailtmp, DNAstrand& to_splice_in) {
  Node* h = nullptr;
  if (headtmp == nullptr) {
    h = head_;
  } else {
    h = headtmp->next;
  }
  while (h != nullptr && h != tailtmp) {
    Node* temp = h->next;
    delete h;
    h = temp;
  }

  if (headtmp == nullptr) {
    head_ = to_splice_in.head_;
    if (tailtmp == nullptr) {
      tail_ = to_splice_in.tail_;
    } else {
      to_splice_in.tail_->next = tailtmp;
    }
    to_splice_in.head_ = nullptr;
    to_splice_in.tail_ = nullptr;
  } else {
    headtmp->next = to_splice_in.head_;
    if (tailtmp == nullptr) {
      tail_ = to_splice_in.tail_;
    } else {
      to_splice_in.tail_->next = tailtmp;
    }
    to_splice_in.head_ = nullptr;
    to_splice_in.tail_ = nullptr;
  }
}
