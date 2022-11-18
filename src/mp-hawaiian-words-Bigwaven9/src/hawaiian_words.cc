#include <iostream>
#include <string>

#include "functions.hpp"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: ./bin/exec word" << std::endl;
    return 1;
  }

  std::string word = argv[1];

  std::string phonetics = Hawaii(word);
  if (!phonetics.empty())
    std::cout << phonetics << std::endl;
  else
    return 1;
}