#include <iostream>

#include "circular-linked-list.hpp"

int main() {
  CircularLinkedList<int> x;
  x.InsertInOrder(1);
  x.InsertInOrder(0);
  x.InsertInOrder(2);
  x.InsertInOrder(3);
  // x.Reverse();
  CircularLinkedList<int> y = x;
  y = x;
  y.Reverse();
  std::cout << x << std::endl;
  std::cout << y << std::endl;
}
