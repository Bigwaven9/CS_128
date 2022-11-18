#include "functions.hpp"

std::string Identify(std::vector<std::vector<int>>& data,
                     std::vector<std::string>& names,
                     std::string& dna,
                     std::vector<std::string>& strs) {
  std::string ret;
  for (size_t i = 0; i < data.size(); ++i) {
    if (Check(data[i], strs, dna)) {
      return names[i];
    }
  }
  return "No match";
}

bool Check(std::vector<int>& nums,
           std::vector<std::string>& strs,
           std::string& dna) {
  std::string temp;
  for (size_t i = 0; i < nums.size(); ++i) {
    temp.clear();
    for (int j = 0; j < nums[i]; ++j) {
      temp += strs[i];
    }
    if (Check(dna, temp) || Check(dna, temp + strs[i])) return false;
  }
  return true;
}

bool Check(std::string& dna, const std::string& s) {
  std::string temp = s + '#' + dna;
  std::vector<size_t> pi(temp.size(), 0);
  for (size_t i = 1; i < temp.size(); ++i) {
    size_t j = pi[i - 1];
    while (j > 0 && temp[i] != temp[j]) j = pi[j - 1];
    if (temp[i] == temp[j]) j++;
    pi[i] = j;
    if (j + 1 == s.size()) return true;
  }
  return false;
}
