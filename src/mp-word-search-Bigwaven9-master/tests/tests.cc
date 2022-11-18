#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include "catch.hpp"

#include <stdexcept>
#include "CharPositions.hpp"
#include "WordLocation.hpp"
#include "WordSearchSolver.hpp"

class WordSearchSolvertest {
public:
  WordSearchSolvertest(const std::vector<std::vector<char>>& puzzle) {
    puzzle_ = puzzle;
    puzzle_height_ = puzzle_.size();
    puzzle_width_ = puzzle_[0].size();
  }
  WordLocation FindWord(const std::string& word) {
    WordLocation x{};
    x = FindWord(word, CheckDirection::kHorizontal);
    if (!x.word.empty() && !x.char_positions.empty()) return x;
    x = FindWord(word, CheckDirection::kVertical);
    if (!x.word.empty() && !x.char_positions.empty()) return x;
    x = FindWord(word, CheckDirection::kLeftDiag);
    if (!x.word.empty() && !x.char_positions.empty()) return x;
    x = FindWord(word, CheckDirection::kRightDiag);
    if (!x.word.empty() && !x.char_positions.empty()) return x;
    return x;
  }
  WordLocation FindWord(const std::string& word, CheckDirection direction) {
    if (direction == CheckDirection::kHorizontal) {
      for (size_t i = 0; i < puzzle_height_; ++i)
        for (size_t j = 0; j < puzzle_width_ - word.size() + 1; ++j) {
          std::string temp;
          std::vector<CharPositions> v;
          for (size_t t = 0; t < word.size(); ++t)
            temp += puzzle_[i][j + t],
                v.push_back({puzzle_[i][j + t], i, j + t});
          if (temp == word) return {temp, v};
        }
    } else if (direction == CheckDirection::kVertical) {
      for (size_t i = 0; i < puzzle_height_ - word.size() + 1; ++i)
        for (size_t j = 0; j < puzzle_width_; ++j) {
          std::string temp;
          std::vector<CharPositions> v;
          for (size_t t = 0; t < word.size(); ++t)
            temp += puzzle_[i + t][j],
                v.push_back({puzzle_[i + t][j], i + t, j});
          if (temp == word) return {temp, v};
        }
    } else if (direction == CheckDirection::kLeftDiag) {
      for (size_t i = 0; i < puzzle_height_ - word.size() + 1; ++i)
        for (size_t j = word.size() - 1; j < puzzle_width_; ++j) {
          std::string temp;
          std::vector<CharPositions> v;
          for (size_t t = 0; t < word.size(); ++t)
            temp += puzzle_[i + t][j - t],
                v.push_back({puzzle_[i + t][j - t], i + t, j - t});
          if (temp == word) return {temp, v};
        }
    } else
      for (size_t i = 0; i < puzzle_height_ - word.size() + 1; ++i)
        for (size_t j = 0; j < puzzle_width_ - word.size() + 1; ++j) {
          std::string temp;
          std::vector<CharPositions> v;
          for (size_t t = 0; t < word.size(); ++t)
            temp += puzzle_[i + t][j + t],
                v.push_back({puzzle_[i + t][j + t], i + t, j + t});
          if (temp == word) return {temp, v};
        }
    return {};
  }

private:
  bool LocationInBounds(size_t row, size_t col) const {
    return ((row < puzzle_height_) && (col < puzzle_width_) &&
            (row >= 0 && col >= 0));
  }
  std::vector<std::vector<char>> puzzle_;
  size_t puzzle_height_;
  size_t puzzle_width_;
};

char rand_char() { return rand() % 26 + 'a'; }

std::string rand_string(int len) {
  std::string s;
  while (len--) {
    s += rand_char();
  }
  return s;
}

std::vector<std::vector<char>> generate_random_matrix(size_t m, size_t n) {
  std::vector<std::vector<char>> matrix;
  for (size_t i = 0; i < m; ++i) {
    std::vector<char> row;
    for (size_t j = 0; j < n; ++j) {
      row.push_back(rand_char());
    }
    matrix.push_back(row);
  }
  return matrix;
}

void equals(const WordLocation& x, const WordLocation& y) {
  if (x.word.empty()) {
    REQUIRE(y.word.empty());
  }
  if (x.word != y.word || x.char_positions.size() != y.char_positions.size()) {
    REQUIRE_FALSE(true);
  }
  for (size_t i = 0; i < x.char_positions.size(); ++i) {
    if (x.char_positions[i].character != y.char_positions[i].character ||
        x.char_positions[i].row != y.char_positions[i].row ||
        x.char_positions[i].col != y.char_positions[i].col) {
      REQUIRE_FALSE(true);
    }
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("random test", "") {
  srand(time(nullptr));
  for (int c = 0; c < 15; ++c) {
    std::vector<std::vector<char>> v =
        generate_random_matrix(rand() % 10 + 1, rand() % 10 + 1);
    WordSearchSolvertest x(v);
    WordSearchSolver y(v);

    auto find = rand_string(rand() % 10 + 1);

    equals(x.FindWord(find), y.FindWord(find));
    equals(x.FindWord(find, CheckDirection::kHorizontal),
           y.FindWord(find, CheckDirection::kHorizontal));
    equals(x.FindWord(find, CheckDirection::kVertical),
           y.FindWord(find, CheckDirection::kVertical));
    equals(x.FindWord(find, CheckDirection::kRightDiag),
           y.FindWord(find, CheckDirection::kRightDiag));
    equals(x.FindWord(find, CheckDirection::kLeftDiag),
           y.FindWord(find, CheckDirection::kLeftDiag));
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("1 2 3 5 8", "") {
  std::vector<std::vector<char>> v{{'1', '2', '3', '4', '5'},
                                   {'6', '7', '8', '9', 'a'},
                                   {'b', 'c', 'd', 'e', 'f'},
                                   {'g', 'h', 'i', 'j', 'k'},
                                   {'l', 'm', 'n', 'o', 'p'}};
  WordSearchSolver a(v);
  auto x = a.FindWord("17djp");
  auto y = a.FindWord("sdf");
  REQUIRE(y.word.empty());
  REQUIRE(y.char_positions.empty());
  REQUIRE(x.word == "17djp");
  REQUIRE(x.char_positions[0].character == '1');
  REQUIRE(x.char_positions[1].character == '7');
  REQUIRE(x.char_positions[2].character == 'd');
  REQUIRE(x.char_positions[3].character == 'j');
  REQUIRE(x.char_positions[4].character == 'p');
  REQUIRE((x.char_positions[0].row == 0 && x.char_positions[0].col == 0));
  REQUIRE((x.char_positions[1].row == 1 && x.char_positions[1].col == 1));
  REQUIRE((x.char_positions[2].row == 2 && x.char_positions[2].col == 2));
  REQUIRE((x.char_positions[3].row == 3 && x.char_positions[3].col == 3));
  REQUIRE((x.char_positions[4].row == 4 && x.char_positions[4].col == 4));
}

/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("4 10", "") {
  std::vector<std::vector<char>> v{{'1', '2', '3', '4', '5'},
                                   {'6', '7', '8', '9', 'a'},
                                   {'b', 'c', 'd', 'e', 'f'},
                                   {'g', 'h', 'i', 'j', 'k'},
                                   {'l', 'm', 'n', 'o', 'p'}};
  WordSearchSolver a(v);
  auto x = a.FindWord("12345", CheckDirection::kHorizontal);
  REQUIRE(x.word == "12345");
  x = a.FindWord("lmnop", CheckDirection::kHorizontal);
  REQUIRE(x.word == "lmnop");
}

/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("", "") {
  std::vector<std::vector<char>> v{{'1', '2', '3', '4', '5'},
                                   {'6', '7', '8', '9', 'a'},
                                   {'b', 'c', 'd', 'e', 'f'},
                                   {'g', 'h', 'i', 'j', 'k'},
                                   {'l', 'm', 'n', 'o', 'p'}};
  WordSearchSolver a(v);
  auto x = a.FindWord("16bgl", CheckDirection::kVertical);
  REQUIRE(x.word == "16bgl");
  x = a.FindWord("5afkp", CheckDirection::kVertical);
  REQUIRE(x.word == "5afkp");
}

/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("6", "") {
  std::vector<std::vector<char>> v{{'1', '2', '3', '4', '5'},
                                   {'6', '7', '8', '9', 'a'},
                                   {'b', 'c', 'd', 'e', 'f'},
                                   {'g', 'h', 'i', 'j', 'k'},
                                   {'l', 'm', 'n', 'o', 'p'}};
  WordSearchSolver a(v);
  auto x = a.FindWord("17", CheckDirection::kRightDiag);
  REQUIRE(x.word == "17");
  x = a.FindWord("jp", CheckDirection::kRightDiag);
  REQUIRE(x.word == "jp");
  x = a.FindWord("17djp", CheckDirection::kRightDiag);
  REQUIRE(x.word == "17djp");
}

/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("7", "") {
  std::vector<std::vector<char>> v{{'1', '2', '3', '4', '5'},
                                   {'6', '7', '8', '9', 'a'},
                                   {'b', 'c', 'd', 'e', 'f'},
                                   {'g', 'h', 'i', 'j', 'k'},
                                   {'l', 'm', 'n', 'o', 'p'}};
  WordSearchSolver a(v);
  auto x = a.FindWord("59", CheckDirection::kLeftDiag);
  REQUIRE(x.word == "59");
  x = a.FindWord("hl", CheckDirection::kLeftDiag);
  REQUIRE(x.word == "hl");
  x = a.FindWord("59dhl", CheckDirection::kLeftDiag);
  REQUIRE(x.word == "59dhl");
}

/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("", "") {
  std::vector<std::vector<char>> v{{'1', '2', '3', '4', '5'},
                                   {'6', '7', '8', '9', 'a'},
                                   {'b', 'c', '*', '#', 'f'},
                                   {'g', '#', '#', '#', 'k'},
                                   {'l', 'm', 'n', 'o', 'p'}};
  WordSearchSolver a(v);
  auto x = a.FindWord("*#");
  REQUIRE(x.word == "*#");
  x = a.FindWord("*#", CheckDirection::kHorizontal);
  REQUIRE(x.word == "*#");
  x = a.FindWord("*#", CheckDirection::kVertical);
  REQUIRE(x.word == "*#");
  x = a.FindWord("*#", CheckDirection::kLeftDiag);
  REQUIRE(x.word == "*#");
  x = a.FindWord("*#", CheckDirection::kRightDiag);
  REQUIRE(x.word == "*#");
  x = a.FindWord("#*", CheckDirection::kHorizontal);
  REQUIRE((x.word.empty() && x.char_positions.empty()));
}

/////////////////////////////////////////////////////////////////////////////////////////////