#ifndef ILLINI_BOOK_HPP
#define ILLINI_BOOK_HPP

#include <fstream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

#include "utilities.hpp"

using namespace std;
using namespace utilities;

class IlliniBook {
public:
  IlliniBook(const std::string& people_fpath,
             const std::string& relations_fpath) {
    ifstream people{people_fpath}, relations{relations_fpath};
    for (string line; getline(people, line); line.clear())
      if (h_.count(stoi(line)) == 0) h_[stoi(line)] = map<int, string>();
    for (string line; getline(relations, line); line.clear()) {
      vector<string> v = Split(line, ',');
      h_[stoi(v[0])][stoi(v[1])] = v[2];
      h_[stoi(v[1])][stoi(v[0])] = v[2];
    }
  }
  IlliniBook(const IlliniBook& rhs) = delete;
  IlliniBook& operator=(const IlliniBook& rhs) = delete;
  ~IlliniBook() = default;
  bool AreRelated(int uin_1, int uin_2) {
    queue<int> q;
    q.push(uin_1);
    set<int> visited;
    visited.insert(uin_1);
    while (!q.empty()) {
      int t = q.front();
      q.pop();
      if (uin_2 == t) return true;
      for (auto& tt : h_[t]) {
        if (visited.count(tt.first) != 0) continue;
        visited.insert(tt.first);
        q.push(tt.first);
      }
    }
    return false;
  }
  bool AreRelated(int uin_1, int uin_2, const std::string& relationship) {
    queue<int> q;
    q.push(uin_1);
    set<int> visited;
    visited.insert(uin_1);
    while (!q.empty()) {
      int t = q.front();
      q.pop();
      if (uin_2 == t) return true;
      for (auto& tt : h_[t]) {
        if (visited.count(tt.first) != 0 || tt.second != relationship) continue;
        visited.insert(tt.first);
        q.push(tt.first);
      }
    }
    return false;
  }
  int GetRelated(int uin_1, int uin_2) {
    queue<int> q;
    q.push(uin_1);
    set<int> visited;
    visited.insert(uin_1);
    int cnt = 0;
    while (!q.empty()) {
      for (unsigned c = q.size(); c > 0; --c) {
        int t = q.front();
        q.pop();
        if (uin_2 == t) return cnt;
        for (auto& tt : h_[t]) {
          if (visited.count(tt.first) != 0) continue;
          visited.insert(tt.first);
          q.push(tt.first);
        }
      }
      cnt++;
    }
    return -1;
  }
  int GetRelated(int uin_1, int uin_2, const std::string& relationship) {
    queue<int> q;
    q.push(uin_1);
    set<int> visited;
    visited.insert(uin_1);
    int cnt = 0;
    while (!q.empty()) {
      for (unsigned c = q.size(); c > 0; --c) {
        int t = q.front();
        q.pop();
        if (uin_2 == t) return cnt;
        for (auto& tt : h_[t]) {
          if (visited.count(tt.first) != 0 || tt.second != relationship)
            continue;
          visited.insert(tt.first);
          q.push(tt.first);
        }
      }
      cnt++;
    }
    return -1;
  }
  std::vector<int> GetSteps(int uin, int n) {
    queue<int> q;
    q.push(uin);
    set<int> visited;
    visited.insert(uin);
    for (; n > 0; --n) {
      for (unsigned c = q.size(); c > 0; --c) {
        int t = q.front();
        q.pop();
        for (auto& tt : h_[t]) {
          if (visited.count(tt.first) != 0) continue;
          visited.insert(tt.first);
          q.push(tt.first);
        }
      }
    }
    vector<int> ret;
    while (!q.empty()) ret.push_back(q.front()), q.pop();
    return ret;
  }
  size_t CountGroups() {
    set<int> visited;
    size_t cnt = 0;
    for (auto& i : h_) {
      if (visited.count(i.first) != 0) continue;
      queue<int> q;
      q.push(i.first);
      cnt++;
      while (!q.empty()) {
        int t = q.front();
        q.pop();
        for (auto& tt : h_[t]) {
          if (visited.count(tt.first) != 0) continue;
          visited.insert(tt.first);
          q.push(tt.first);
        }
      }
    }
    return cnt;
  }
  size_t CountGroups(const std::string& relationship) {
    set<int> visited;
    size_t cnt = 0;
    for (auto& i : h_) {
      if (visited.count(i.first) != 0) continue;
      queue<int> q;
      q.push(i.first);
      visited.insert(i.first);
      cnt++;
      while (!q.empty()) {
        int t = q.front();
        q.pop();
        for (auto& [x, y] : h_[t]) {
          if (visited.count(x) != 0 || y != relationship) continue;
          visited.insert(x);
          q.push(x);
        }
      }
    }
    return cnt;
  }
  size_t CountGroups(const std::vector<std::string>& relationships) {
    set<string> relationship;
    for (const auto& i : relationships) relationship.insert(i);
    set<int> visited;
    size_t cnt = 0;
    for (auto& i : h_) {
      if (visited.count(i.first) != 0) continue;
      queue<int> q;
      q.push(i.first);
      visited.insert(i.first);
      cnt++;
      while (!q.empty()) {
        int t = q.front();
        q.pop();
        for (auto& tt : h_[t]) {
          if (visited.count(tt.first) != 0 ||
              relationship.count(tt.second) == 0)
            continue;
          visited.insert(tt.first);
          q.push(tt.first);
        }
      }
    }
    return cnt;
  }

private:
  map<int, map<int, string>> h_;
};

#endif
