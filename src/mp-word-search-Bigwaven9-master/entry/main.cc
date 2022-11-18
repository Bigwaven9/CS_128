#include "../includes/WordSearchSolver.hpp"

int main() {
  std::vector<std::vector<char>> v{{'d', 'e', 'a', 'o', 'u'},
                                   {'h', 'e', 'l', 'l', 'o'},
                                   {'c', 'a', 'l', 'o', 'm'},
                                   {'a', 'e', 't', 'a', 'u'},
                                   {'t', 'e', 't', 'o', 'u'}};
  WordSearchSolver a(v);
  auto x = a.FindWord("ullet");
  for (auto i : x.char_positions) {
    std::cout << i.row << ' ' << i.col << std::endl;
  }
}