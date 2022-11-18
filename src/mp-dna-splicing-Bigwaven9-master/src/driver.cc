#include <iostream>

#include "dna_strand.hpp"

int main() {
  char a[23] = {'c', 't', 'a', 't', 'a'};
  char b[23] = {'1', '2', '3'};
  char c[5] = {'c'};
  auto* x = new DNAstrand(a);
  auto* y = new DNAstrand(b);
  x->SpliceIn(c, *y);
  x->print();
  delete x;
  delete y;
}