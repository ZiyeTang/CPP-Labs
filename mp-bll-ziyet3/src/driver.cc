#include <iostream>

#include "branched-linked-list.hpp"

int main() {
  /* EXAMPLE INTERACTIONS WITH BLL */
  // BLL* first = new BLL();
  // first->PushBack('h');
  // first->PushBack('i');

  // std::cout << first->ToString() << std::endl; // hi
  // std::cout << first->Size() << std::endl; // 2

  // /////////////////////////////////////

  // BLL* second = new BLL();
  // second->PushBack('i');
  // second->PushBack('!');
  // second->PushBack('@');

  // std::cout << second->ToString() << std::endl; // i!@
  // std::cout << second->Size() << std::endl; // 3

  // /////////////////////////////////////

  // first->Join(1, second);

  // std::cout << first->ToString() << std::endl; // hii!@
  // std::cout << first->Size() << std::endl; // 5

  // std::cout << second->ToString() << std::endl; // i!@
  // std::cout << second->Size() << std::endl; // 3

  // /////////////////////////////////////

  // BLL* first_clone = new BLL();
  // *first_clone = *first;

  // std::cout << first_clone->ToString() << std::endl; // hii!@
  // std::cout << first_clone->Size() << std::endl; // 5

  return 0;
}
