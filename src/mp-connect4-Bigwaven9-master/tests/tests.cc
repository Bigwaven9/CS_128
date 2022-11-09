// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Michael R. Nowak                Environment : ubuntu:latest               //
//  Date ......: 2022/02/07                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "board.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
constexpr int kBoardWidth = 7;
constexpr int kBoardHeight = 6;

bool AreEqual(DiskType solution[][kBoardWidth],
              DiskType student[][kBoardWidth]) {
  for (int i = 0; i < kBoardHeight; ++i) {
    for (int j = 0; j < kBoardWidth; ++j) {
      if (solution[i][j] != student[i][j]) return false;
    }
  }
  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Board initialization", "[board_init]") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE(AreEqual(solution, student.board));
}

/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Drop disk to board", "[drop]") {
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kPlayer1}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  DropDiskToBoard(student, DiskType::kPlayer1, Board::kBoardWidth - 1);
  REQUIRE(AreEqual(solution, student.board));
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, -2),
                    std::runtime_error);
  REQUIRE_THROWS_AS(
      DropDiskToBoard(student, DiskType::kPlayer1, Board::kBoardWidth),
      std::runtime_error);
  for (int i = 0; i < Board::kBoardHeight; ++i)
    DropDiskToBoard(student, DiskType::kPlayer1, 0);
  REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 0),
                    std::runtime_error);
}

/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("horizontal", "[horizontal]") {
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kHorizontal) == false);
  for (int i = 0; i < Board::kBoardWidth - 1; ++i) {
    if (i < 3)
      DropDiskToBoard(student, DiskType::kPlayer1, i);
    else
      DropDiskToBoard(student, DiskType::kPlayer2, i);
  }
  SECTION("basic") {
    DropDiskToBoard(student, DiskType::kPlayer2, Board::kBoardWidth - 1);
    std::cout << BoardToStr(student) << std::endl;
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE_FALSE(CheckForWinner(student, DiskType::kPlayer1));
    for (int i = 2; i < 6; ++i) {
      DropDiskToBoard(student, DiskType::kPlayer1, i);
    }
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("vertical", "[vertical]") {
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kHorizontal) == false);
  for (int i = 0; i < Board::kBoardHeight; ++i)
    DropDiskToBoard(student, DiskType::kPlayer1, i);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kHorizontal) == true);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer2,
                          WinningDirection::kHorizontal) == false);
}

/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("rightDiag", "[rightDiag]") {
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kRightDiag) == false);
  for (int i = 0; i < Board::kBoardWidth; ++i)
    for (int j = 0; j < Board::kBoardHeight; ++j)
      if (i == j)
        DropDiskToBoard(student, DiskType::kPlayer1, i);
      else
        DropDiskToBoard(student, DiskType::kPlayer2, i);

  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kRightDiag) == true);
}

/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("leftDiag", "[leftDiag]") {
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kLeftDiag) == false);
  for (int i = 0; i < Board::kBoardWidth; ++i)
    for (int j = Board::kBoardHeight - i - 1; j >= 0; --j)
      if (j == 0)
        DropDiskToBoard(student, DiskType::kPlayer1, i);
      else
        DropDiskToBoard(student, DiskType::kPlayer2, i);

  REQUIRE(SearchForWinner(student,
                          DiskType::kPlayer1,
                          WinningDirection::kLeftDiag) == true);
}

/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("bound", "[bound]") {
  REQUIRE(BoardLocationInBounds(0, 0));
  REQUIRE(BoardLocationInBounds(2, 4));
  REQUIRE(BoardLocationInBounds(0, -1) == false);
  REQUIRE(BoardLocationInBounds(0, Board::kBoardWidth) == false);
  REQUIRE(BoardLocationInBounds(-1, 0) == false);
  REQUIRE(BoardLocationInBounds(Board::kBoardHeight, 0) == false);
}

/////////////////////////////////////////////////////////////////////////////////////////////

// std::cout << BoardToStr(student) << std::endl;

TEST_CASE("lefttop", "[lefttop]") {
  Board student;  // NOLINT
  InitBoard(student);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < Board::kBoardHeight - 4; ++j) {
      if (((i == 0 || i == 3) && j % 2 == 0) ||
          ((i == 1 || i == 2) && j % 2 == 1))
        DropDiskToBoard(student, DiskType::kPlayer1, i);
      else
        DropDiskToBoard(student, DiskType::kPlayer2, i);
    }
  }
  SECTION("hori") {
    for (int i = 0; i < 4; ++i) {
      for (int j = Board::kBoardHeight - 4; j < Board::kBoardHeight - 1; ++j) {
        if (((i == 0 || i == 3) && j % 2 == 0) ||
            ((i == 1 || i == 2) && j % 2 == 1))
          DropDiskToBoard(student, DiskType::kPlayer1, i);
        else
          DropDiskToBoard(student, DiskType::kPlayer2, i);
      }
    }
    for (int i = 0; i < 4; ++i) {
      DropDiskToBoard(student, DiskType::kPlayer2, i);
    }
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE(SearchForWinner(student,
                            DiskType::kPlayer1,
                            WinningDirection::kHorizontal) == false);
  }
  SECTION("verti") {
    for (int i = 0; i < 4; ++i) {
      DropDiskToBoard(student, DiskType::kPlayer1, 0);
    }
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE(SearchForWinner(student,
                            DiskType::kPlayer2,
                            WinningDirection::kVertical) == false);
  }
  SECTION("left") {
    for (int i = 0; i < 4; ++i) {
      for (int j = 3 - i; j >= 0; --j) {
        if (j == 0)
          DropDiskToBoard(student, DiskType::kPlayer1, i);
        else
          DropDiskToBoard(student, DiskType::kPlayer2, i);
      }
    }
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  }
  SECTION("right") {
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < i + 1; ++j) {
        if (i == j)
          DropDiskToBoard(student, DiskType::kPlayer1, i);
        else
          DropDiskToBoard(student, DiskType::kPlayer2, i);
      }
    }
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("righttop", "[righttop]") {
  Board student;  // NOLINT
  InitBoard(student);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < Board::kBoardHeight - 4; ++j) {
      if (((i == 0 || i == 3) && j % 2 == 0) ||
          ((i == 1 || i == 2) && j % 2 == 1))
        DropDiskToBoard(
            student, DiskType::kPlayer1, i + Board::kBoardWidth - 4);
      else
        DropDiskToBoard(
            student, DiskType::kPlayer2, i + Board::kBoardWidth - 4);
    }
  }
  SECTION("hori") {
    for (int i = 0; i < 4; ++i) {
      for (int j = Board::kBoardHeight - 4; j < Board::kBoardHeight - 1; ++j) {
        if (((i == 0 || i == 3) && j % 2 == 0) ||
            ((i == 1 || i == 2) && j % 2 == 1))
          DropDiskToBoard(
              student, DiskType::kPlayer1, i + Board::kBoardWidth - 4);
        else
          DropDiskToBoard(
              student, DiskType::kPlayer2, i + Board::kBoardWidth - 4);
      }
    }
    for (int i = 0; i < 4; ++i) {
      DropDiskToBoard(student, DiskType::kPlayer2, i + Board::kBoardWidth - 4);
    }
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE(SearchForWinner(student,
                            DiskType::kPlayer1,
                            WinningDirection::kHorizontal) == false);
  }
  SECTION("verti") {
    for (int i = 0; i < 4; ++i) {
      DropDiskToBoard(student, DiskType::kPlayer1, Board::kBoardWidth - 4);
    }
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE(SearchForWinner(student,
                            DiskType::kPlayer2,
                            WinningDirection::kVertical) == false);
  }
  SECTION("left") {
    for (int i = 0; i < 4; ++i) {
      for (int j = 3 - i; j >= 0; --j) {
        if (j == 0)
          DropDiskToBoard(
              student, DiskType::kPlayer1, i + Board::kBoardWidth - 4);
        else
          DropDiskToBoard(
              student, DiskType::kPlayer2, i + Board::kBoardWidth - 4);
      }
    }
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  }
  SECTION("right") {
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < i + 1; ++j) {
        if (i == j)
          DropDiskToBoard(
              student, DiskType::kPlayer1, i + Board::kBoardWidth - 4);
        else
          DropDiskToBoard(
              student, DiskType::kPlayer2, i + Board::kBoardWidth - 4);
      }
    }
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("rightbuttom", "[rightbuttom]") {
  Board student;  // NOLINT
  InitBoard(student);
  SECTION("hori") {
    for (int i = 0; i < 4; ++i) {
      for (int j = Board::kBoardHeight - 4; j < Board::kBoardHeight - 1; ++j) {
        if (((i == 0 || i == 3) && j % 2 == 0) ||
            ((i == 1 || i == 2) && j % 2 == 1))
          DropDiskToBoard(
              student, DiskType::kPlayer1, i + Board::kBoardWidth - 4);
        else
          DropDiskToBoard(
              student, DiskType::kPlayer2, i + Board::kBoardWidth - 4);
      }
    }
    for (int i = 0; i < 4; ++i) {
      DropDiskToBoard(student, DiskType::kPlayer2, i + Board::kBoardWidth - 4);
    }
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE(SearchForWinner(student,
                            DiskType::kPlayer1,
                            WinningDirection::kHorizontal) == false);
  }
  SECTION("verti") {
    for (int i = 0; i < 4; ++i) {
      DropDiskToBoard(student, DiskType::kPlayer1, Board::kBoardWidth - 4);
    }
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE(SearchForWinner(student,
                            DiskType::kPlayer2,
                            WinningDirection::kVertical) == false);
  }
  SECTION("left") {
    for (int i = 0; i < 4; ++i) {
      for (int j = 3 - i; j >= 0; --j) {
        if (j == 0)
          DropDiskToBoard(
              student, DiskType::kPlayer1, i + Board::kBoardWidth - 4);
        else
          DropDiskToBoard(
              student, DiskType::kPlayer2, i + Board::kBoardWidth - 4);
      }
    }
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    // REQUIRE(SearchForWinner(student, DiskType::kPlayer2,
    // WinningDirection::kLeftDiag));
  }
  SECTION("right") {
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < i + 1; ++j) {
        if (i == j)
          DropDiskToBoard(
              student, DiskType::kPlayer1, i + Board::kBoardWidth - 4);
        else
          DropDiskToBoard(
              student, DiskType::kPlayer2, i + Board::kBoardWidth - 4);
      }
    }
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    // REQUIRE(SearchForWinner(student, DiskType::kPlayer2,
    // WinningDirection::kRightDiag));
  }
  // std::cout << BoardToStr(student) << std::endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("leftbottom", "[leftbottom]") {
  Board student;  // NOLINT
  InitBoard(student);
  SECTION("hori") {
    for (int i = 0; i < 4; ++i) {
      for (int j = Board::kBoardHeight - 4; j < Board::kBoardHeight - 1; ++j) {
        if (((i == 0 || i == 3) && j % 2 == 0) ||
            ((i == 1 || i == 2) && j % 2 == 1))
          DropDiskToBoard(student, DiskType::kPlayer1, i);
        else
          DropDiskToBoard(student, DiskType::kPlayer2, i);
      }
    }
    for (int i = 0; i < 4; ++i) {
      DropDiskToBoard(student, DiskType::kPlayer2, i);
    }
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE(SearchForWinner(student,
                            DiskType::kPlayer1,
                            WinningDirection::kHorizontal) == false);
  }
  SECTION("verti") {
    for (int i = 0; i < 4; ++i) {
      DropDiskToBoard(student, DiskType::kPlayer1, 0);
    }
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE(SearchForWinner(student,
                            DiskType::kPlayer2,
                            WinningDirection::kVertical) == false);
  }
  SECTION("left") {
    for (int i = 0; i < 4; ++i) {
      for (int j = 3 - i; j >= 0; --j) {
        if (j == 0)
          DropDiskToBoard(student, DiskType::kPlayer1, i);
        else
          DropDiskToBoard(student, DiskType::kPlayer2, i);
      }
    }
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    // REQUIRE(SearchForWinner(student, DiskType::kPlayer2,
    // WinningDirection::kLeftDiag));
  }
  SECTION("right") {
    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < i + 1; ++j) {
        if (i == j)
          DropDiskToBoard(student, DiskType::kPlayer1, i);
        else
          DropDiskToBoard(student, DiskType::kPlayer2, i);
      }
    }
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    // REQUIRE(SearchForWinner(student, DiskType::kPlayer2,
    // WinningDirection::kRightDiag));
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("check", "[check]") {
  Board student;
  InitBoard(student);
  DropDiskToBoard(student, DiskType::kPlayer2, 0);
  DropDiskToBoard(student, DiskType::kPlayer1, 0);
  for (int i = 4; i < 7; ++ i) DropDiskToBoard(student, DiskType::kPlayer1, i);
  REQUIRE(CheckForWinner(student, DiskType::kPlayer1) == false);
  REQUIRE(CheckForWinner(student, DiskType::kPlayer2) == false);
}