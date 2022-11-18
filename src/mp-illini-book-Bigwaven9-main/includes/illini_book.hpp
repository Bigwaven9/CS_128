#ifndef ILLINI_BOOK_HPP
#define ILLINI_BOOK_HPP

#include <fstream>
#include <map>
#include <queue>
#include <set>
#include <string>

#include "utilities.hpp"

using namespace utilities;
using namespace std;

class Graph {
private:
  int idx_ = 0;
  map<int, int> h_;
  map<int, int> e_;
  map<int, int> ne_;
  map<int, string> w_;

public:
  Graph() = default;
  void Add(int a, int b, string& c) {
    e_[++idx_] = b, w_[idx_] = c, ne_[idx_] = h_[a], h_[a] = idx_;
  }
  void Add(int a) { h_[a] = 0; }

  int Connected(int a, int b) {
    int cnt = 0;
    queue<int> q;
    q.push(a);
    set<int> st;
    st.insert(a);
    while (!q.empty()) {
      for (unsigned x = q.size(); x != 0; --x) {
        int t = q.front();
        q.pop();
        if (t == b) return cnt;
        for (int i = h_[t]; i != 0; i = ne_[i]) {
          int j = e_[i];
          if (st.count(j) == 0) {
            q.push(j);
            st.insert(j);
          }
        }
      }
      cnt++;
    }
    return -1;
  }

  int Connected(int a, int b, const string& c) {
    int cnt = 0;
    queue<int> q;
    q.push(a);
    set<int> st;
    st.insert(a);
    while (!q.empty()) {
      for (unsigned x = q.size(); x != 0; --x) {
        int t = q.front();
        q.pop();
        if (t == b) return cnt;
        for (int i = h_[t]; i != 0; i = ne_[i]) {
          int j = e_[i];
          if (st.count(j) == 0 && w_[i] == c) {
            q.push(j);
            st.insert(j);
          }
        }
      }
      cnt++;
    }
    return -1;
  }

  vector<int> GetSteps(int a, int n) {
    queue<int> q;
    q.push(a);
    set<int> st;
    st.insert(a);
    while (!q.empty() && n-- != 0) {
      for (unsigned x = q.size(); x != 0; --x) {
        int t = q.front();
        q.pop();
        for (int i = h_[t]; i != 0; i = ne_[i]) {
          int j = e_[i];
          if (st.count(j) == 0) {
            q.push(j);
            st.insert(j);
          }
        }
      }
    }
    vector<int> v;
    while (!q.empty()) v.push_back(q.front()), q.pop();
    return v;
  }

  size_t CountGroups() {
    size_t cnt = 0;
    set<int> st;
    for (auto& [x, y] : h_) {
      if (st.count(x) == 0) {
        queue<int> q;
        q.push(x);
        st.insert(x);
        while (!q.empty()) {
          int t = q.front();
          q.pop();
          for (int i = h_[t]; i != 0; i = ne_[i]) {
            int j = e_[i];
            if (st.count(j) == 0) {
              q.push(j);
              st.insert(j);
            }
          }
        }
        cnt++;
      }
    }
    return cnt;
  }

  size_t CountGroups(const string& relationship) {
    size_t cnt = 0;
    set<int> st;
    for (auto& [x, y] : h_) {
      if (st.count(x) == 0) {
        queue<int> q;
        q.push(x);
        st.insert(x);
        while (!q.empty()) {
          int t = q.front();
          q.pop();
          for (int i = h_[t]; i != 0; i = ne_[i]) {
            int j = e_[i];
            if (st.count(j) == 0 && w_[i] == relationship) {
              q.push(j);
              st.insert(j);
            }
          }
        }
        cnt++;
      }
    }
    return cnt;
  }

  size_t CountGroups(const vector<string>& relationships_) {
    set<string> relationships;
    for (const auto& i : relationships_) relationships.insert(i);
    size_t cnt = 0;
    set<int> st;
    for (auto& [x, y] : h_) {
      if (st.count(x) == 0) {
        queue<int> q;
        q.push(x);
        st.insert(x);
        while (!q.empty()) {
          int t = q.front();
          q.pop();
          for (int i = h_[t]; i != 0; i = ne_[i]) {
            int j = e_[i];
            if (st.count(j) == 0 && relationships.count(w_[i]) != 0) {
              q.push(j);
              st.insert(j);
            }
          }
        }
        cnt++;
      }
    }
    return cnt;
  }
};

class IlliniBook {
private:
  Graph g_;

public:
  IlliniBook(const std::string& people_fpath,
             const std::string& relations_fpath);
  IlliniBook(const IlliniBook& rhs) = delete;
  IlliniBook& operator=(const IlliniBook& rhs) = delete;
  ~IlliniBook() = default;
  bool AreRelated(int uin_1, int uin_2);
  bool AreRelated(int uin_1, int uin_2, const std::string& relationship);
  int GetRelated(int uin_1, int uin_2);
  int GetRelated(int uin_1, int uin_2, const std::string& relationship);
  std::vector<int> GetSteps(int uin, int n);
  size_t CountGroups();
  size_t CountGroups(const std::string& relationship);
  size_t CountGroups(const std::vector<std::string>& relationships);
};

#endif
