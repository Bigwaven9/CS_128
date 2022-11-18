#include "board.hpp"

// you might need additional includes
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

/**************************************************************************/
/* your function definitions                                              */
/**************************************************************************/

void InitBoard(Board& b) {
  // below was minimal to get tests to actually compile and given test case to
  // fail
  for (int i = 0; i < Board::kBoardHeight; ++i)
    for (int j = 0; j < Board::kBoardWidth; ++j)
      b.board[i][j] = DiskType::kEmpty;
}

/**************************************************************************/
/* provided to you                                                        */
/**************************************************************************/
std::string BoardToStr(const Board& b) {
  constexpr int kTotalWidth = Board::kBoardWidth * 11 - Board::kBoardHeight - 1;
  std::stringstream ss;
  ss << std::endl;
  for (int row = Board::kBoardHeight; row > 0; --row) {
    ss << " |";
    for (int col = 0; col < Board::kBoardWidth; ++col) {
      std::string value_here;
      value_here.push_back(static_cast<char>(b.board[row - 1][col]));
      ss << ' ' << CenterStr(value_here, Board::kBoardWidth + 1) << '|';
    }
    ss << std::endl;
    ss << " |" << std::setw(kTotalWidth) << std::setfill('-') << '|'
       << std::endl;
  }
  ss << " |";
  for (int col = 0; col < Board::kBoardWidth; ++col) {
    ss << ' ' << CenterStr(std::to_string(col), Board::kBoardWidth + 1) << '|';
  }
  return ss.str();
}

std::string CenterStr(const std::string& str, int col_width) {
  // quick and easy (but error-prone) implementation
  auto padl = (col_width - str.length()) / 2;
  auto padr = (col_width - str.length()) - padl;
  std::string strf = std::string(padl, ' ') + str + std::string(padr, ' ');
  return strf;
}

void DropDiskToBoard(Board& b, DiskType disk, int col) {
  if (col >= Board::kBoardWidth || col < 0)
    throw std::runtime_error("exceed column");
  for (int i = 0; i < Board::kBoardHeight; ++i)
    if (b.board[i][col] == DiskType::kEmpty) {
      b.board[i][col] = disk;
      return;
    }
  throw std::runtime_error("");
}

bool CheckForWinner(Board& b, DiskType disk) {
  return SearchForWinner(b, disk, WinningDirection::kHorizontal) ||
         SearchForWinner(b, disk, WinningDirection::kVertical) ||
         SearchForWinner(b, disk, WinningDirection::kRightDiag) ||
         SearchForWinner(b, disk, WinningDirection::kLeftDiag);
}

bool SearchForWinner(Board& b, DiskType disk, WinningDirection to_check) {
  if (to_check == WinningDirection::kHorizontal) {
    for (int i = 0; i < Board::kBoardHeight; ++i)
      for (int j = 0; j < Board::kBoardWidth - 3; ++j)
        if (disk == b.board[i][j + 1] && disk == b.board[i][j + 2] &&
            disk == b.board[i][j + 3] && b.board[i][j] == disk)
          return true;
  } else if (to_check == WinningDirection::kVertical) {
    for (int i = 0; i < Board::kBoardHeight - 3; ++i)
      for (int j = 0; j < Board::kBoardWidth; ++j)
        if (disk == b.board[i + 1][j] && disk == b.board[i + 2][j] &&
            disk == b.board[i + 3][j] && b.board[i][j] == disk)
          return true;
  } else if (to_check == WinningDirection::kRightDiag) {
    for (int i = 0; i < Board::kBoardHeight - 3; ++i)
      for (int j = 0; j < Board::kBoardWidth - 3; ++j)
        if (disk == b.board[i + 1][j + 1] && disk == b.board[i + 2][j + 2] &&
            disk == b.board[i + 3][j + 3] && b.board[i][j] == disk)
          return true;
  } else if (to_check == WinningDirection::kLeftDiag) {
    for (int i = 3; i < Board::kBoardHeight; ++i)
      for (int j = 0; j < Board::kBoardWidth - 3; ++j)
        if (disk == b.board[i - 1][j + 1] && disk == b.board[i - 2][j + 2] &&
            disk == b.board[i - 3][j + 3] && b.board[i][j] == disk)
          return true;
  }
  return false;
}

bool BoardLocationInBounds(int row, int col) {
  return row >= 0 && col >= 0 && row < Board::kBoardHeight && col < Board::kBoardWidth;
}