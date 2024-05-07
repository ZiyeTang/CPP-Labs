#ifndef BRANCHED_LINKED_LIST_HPP
#define BRANCHED_LINKED_LIST_HPP

#include <cstddef>
#include <stdexcept>
#include <string>

#include "node.hpp"

class BLL {
 public:
  BLL();
  BLL(const BLL& to_copy);
  ~BLL();

  BLL& operator=(const BLL& rhs);
  Node* PushBack(char dat);
  char GetAt(size_t idx) const;
  void SetAt(size_t idx, char dat);
  void Join(size_t idx, BLL* list);
  std::string ToString() const;
  size_t Size() const;

 private:
  Node* head_;
  bool IsBLLAcyclic() const;
  void Copy(const BLL& to_copy, Node*& head);
  void Destroy();
  size_t SizeHelper(const BLL* bll) const;
  std::string ToStringHelper(const BLL* bll) const;
  Node* GetNodeAt(size_t& idx, Node* head) const;
};

#endif
