#include "functions.hpp"
// Your function definitions should go in this source file.

#include <cctype>
#include <iostream>
#include <map>
#include <string>
#include <vector>

std::map<char, std::string> vowel{
    {'a', "ah"}, {'e', "eh"}, {'i', "ee"}, {'o', "oh"}, {'u', "oo"}};
std::map<std::string, std::string> vowels{{"ai", "eye"},
                                          {"ae", "eye"},
                                          {"ao", "ow"},
                                          {"au", "ow"},
                                          {"ei", "ay"},
                                          {"eu", "eh-oo"},
                                          {"iu", "ew"},
                                          {"oi", "oy"},
                                          {"ou", "ow"},
                                          {"ui", "ooey"}};

std::map<char, int> m{{'a', 1},
                      {'e', 1},
                      {'i', 1},
                      {'o', 1},
                      {'u', 1},
                      {'p', 1},
                      {'k', 1},
                      {'h', 1},
                      {'l', 1},
                      {'m', 1},
                      {'n', 1},
                      {' ', 1},
                      {'\'', 1},
                      {'w', 1}};

std::string Help(const std::string& word) {
  std::string str;
  for (const auto& i : word) {
    str += tolower(i);
  }
  return str;
}

void Help2(std::string& to_return, std::string& temp) {
  if (temp.size() == 1) {
    to_return += vowel[temp[0]];
  } else if (temp.size() == 2) {
    to_return += vowels[temp];
  }
}

std::string Change(const std::string& str) {
  std::string to_return, temp;
  for (unsigned i = 0; i < str.size();) {
    if (temp.empty()) {
      if (vowel.count(str[i]) != 0) {
        temp += str[i++];
      } else {
        if (str[i] == 'w' && i >= 1 &&
            (str[i - 1] == 'i' || str[i - 1] == 'e')) {
          to_return += 'v';
          i++;
        } else {
          to_return += str[i++];
        }
      }
    } else if (temp.size() == 1) {
      if (vowels.count(temp + str[i]) != 0) {
        temp += str[i++];
      } else {
        if (str[i] == ' ' || str[i] == '\'') {
          to_return += vowel[temp[0]];
        } else {
          to_return += vowel[temp[0]] + '-';
        }
        temp.clear();
      }
    } else {
      if (str[i] == ' ' || str[i] == '\'') {
        to_return += vowels[temp];
      } else {
        to_return += vowels[temp] + '-';
      }
      temp.clear();
    }
  }

  Help2(to_return, temp);
  return to_return;
}

bool Check(const std::string& str) {
  for (unsigned i = 0; i < str.size(); i++) {
    if (m.count(str[i]) == 0) {
      return false;
    }
  }
  return true;
}

std::string Hawaii(const std::string& word) {
  std::string str = Help(word);
  if (Check(str)) {
    return Change(str);
  }
  str = word;
  return str + "contains a character not a part of the Hawaiian language.";
};