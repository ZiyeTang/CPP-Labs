#ifndef DNA_STRAND_HPP
#define DNA_STRAND_HPP

#include <stdexcept>

#include "node.hpp"

class DNAstrand {
public:
  DNAstrand() = default;
  DNAstrand(const DNAstrand& rhs) = delete;
  DNAstrand& operator=(const DNAstrand& rhs) = delete;
  ~DNAstrand();

  void SpliceIn(const char* pattern, DNAstrand& to_splice_in);

private:
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
  void Insert(Node* headtmp, Node* tailtmp, DNAstrand& to_splice_in);
  void Remove(Node* headtmp, Node* tailtmp);
};

#endif