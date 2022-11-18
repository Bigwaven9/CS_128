#include <iostream>

#include "branched-linked-list.hpp"

int main() {
  /* EXAMPLE INTERACTIONS WITH BLL */
  BLL* first = new BLL();
  first->PushBack('a');
  first->PushBack('b');

  // std::cout << first->ToString() << std::endl;  // hi
  // std::cout << first->Size() << std::endl;      // 2

  // /////////////////////////////////////

  BLL* second = new BLL();
  second->PushBack('c');
  second->PushBack('d');
  second->PushBack('e');

  // std::cout << second->ToString() << std::endl;  // i!@
  // std::cout << second->Size() << std::endl;      // 3

  // /////////////////////////////////////

  first->Join(1, second);
  second->Join(2, first);
  // if (first->IsBLLAcyclic()) std::cout << "yes" << std::endl;

  std::cout << first->ToString() << std::endl;  // abcde
  // std::cout << first->Size() << std::endl;      // 5

  std::cout << second->ToString() << std::endl;  // cde
  // std::cout << second->Size() << std::endl;      // 3

  // /////////////////////////////////////

  // BLL* first_clone = new BLL();
  // *first_clone = *first;
  // first_clone->SetAt(2, '2');

  // std::cout << first_clone->ToString() << std::endl;  // hii!@
  // std::cout << first_clone->Size() << std::endl;      // 5

  return 0;
}
