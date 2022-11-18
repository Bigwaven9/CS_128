#include <fstream>
#include <iostream>
#include <string>

#include "functions.hpp"
#include "utilities.hpp"

std::vector<std::vector<int>> data;
std::vector<std::string> names;
std::vector<std::string> strs;

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " [input_file] [dna_sequence]"
              << std::endl;
    return 1;
  }
  std::vector<std::string> temp;
  std::vector<int> tempdata;
  std::string dna = argv[2];
  std::ifstream ifs{argv[1]};
  std::string line;
  std::getline(ifs, line);
  temp = utilities::GetSubstrs(line, ',');
  for (size_t i = 1; i < temp.size(); ++i) {
    strs.push_back(temp[i]);
  }
  for (; std::getline(ifs, line); line = "") {
    temp = utilities::GetSubstrs(line, ',');
    names.push_back(temp[0]);
    for (size_t i = 1; i < temp.size(); ++i) {
      tempdata.push_back(std::stoi(temp[i]));
    }
    data.push_back(tempdata);
    tempdata.clear();
  }
  std::cout << Identify(data, names, dna, strs) << std::endl;

  return 0;
}