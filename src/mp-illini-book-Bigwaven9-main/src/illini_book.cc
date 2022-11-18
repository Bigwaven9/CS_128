#include "illini_book.hpp"

IlliniBook::IlliniBook(const std::string& people_fpath,
                       const std::string& relations_fpath) {
  ifstream people{people_fpath}, relation{relations_fpath};
  for (string line; getline(people, line); line.clear()) g_.Add(stoi(line));
  for (string line; getline(relation, line); line.clear()) {
    vector<string> v = Split(line, ',');
    g_.Add(stoi(v[0]), stoi(v[1]), v[2]);
    g_.Add(stoi(v[1]), stoi(v[0]), v[2]);
  }
}

bool IlliniBook::AreRelated(int uin_1, int uin_2) {
  return g_.Connected(uin_1, uin_2) != -1;
}

bool IlliniBook::AreRelated(int uin_1,
                            int uin_2,
                            const std::string& relationship) {
  return g_.Connected(uin_1, uin_2, relationship) != -1;
}

int IlliniBook::GetRelated(int uin_1, int uin_2) {
  return g_.Connected(uin_1, uin_2);
}

int IlliniBook::GetRelated(int uin_1,
                           int uin_2,
                           const std::string& relationship) {
  return g_.Connected(uin_1, uin_2, relationship);
}

std::vector<int> IlliniBook::GetSteps(int uin, int n) {
  return g_.GetSteps(uin, n);
}

size_t IlliniBook::CountGroups() { return g_.CountGroups(); }

size_t IlliniBook::CountGroups(const std::string& relationship) {
  return g_.CountGroups(relationship);
}

size_t IlliniBook::CountGroups(const std::vector<std::string>& relationships) {
  return g_.CountGroups(relationships);
}