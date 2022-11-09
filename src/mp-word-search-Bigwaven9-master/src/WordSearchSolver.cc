#include "WordSearchSolver.hpp"

bool WordSearchSolver::LocationInBounds(size_t row, size_t col) const {
  return ((row < puzzle_height_) && (col < puzzle_width_) &&
          (row >= 0 && col >= 0));
}

WordSearchSolver::WordSearchSolver(
    const std::vector<std::vector<char>>& puzzle) {
  puzzle_ = puzzle;
  puzzle_height_ = puzzle_.size();
  puzzle_width_ = puzzle_[0].size();
}

WordLocation WordSearchSolver::FindWord(const std::string& word) {
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

WordLocation WordSearchSolver::FindWord(const std::string& word, CheckDirection direction) {
  if (direction == CheckDirection::kHorizontal) {
    for (size_t i = 0; i < puzzle_height_; ++i)
      for (size_t j = 0; j < puzzle_width_ - word.size() + 1; ++j) {
        std::string temp;
        std::vector<CharPositions> v;
        for (size_t t = 0; t < word.size(); ++t)
          temp += puzzle_[i][j + t], v.push_back({puzzle_[i][j + t], i, j + t});
        if (temp == word) return {temp, v};
      }
  } else if (direction == CheckDirection::kVertical) {
    for (size_t i = 0; i < puzzle_height_ - word.size() + 1; ++i)
      for (size_t j = 0; j < puzzle_width_; ++j) {
        std::string temp;
        std::vector<CharPositions> v;
        for (size_t t = 0; t < word.size(); ++t)
          temp += puzzle_[i + t][j], v.push_back({puzzle_[i + t][j], i + t, j});
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