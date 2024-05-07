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

TEST_CASE("drop_results", "[drop_disk_to_board]") {
  Board student;
  InitBoard(student);
  DiskType solution[kBoardHeight][kBoardWidth] = {{DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty},
                                                  {DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty,
                                                   DiskType::kEmpty}};
  for (int i = 0; i < kBoardHeight; i++) {
    DropDiskToBoard(student, DiskType::kPlayer2, 0);
    solution[i][0] = DiskType::kPlayer2;
    REQUIRE(AreEqual(solution, student.board));
  }
}

TEST_CASE("exception_thrown1", "[drop_disk_to_board]") {
  Board student;
  InitBoard(student);
  int range = 50;
  for (int i = 0; i < range; i++) {
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer2, 7 + i),
                      std::runtime_error);
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer2, -1 - i),
                      std::runtime_error);
  }
}

TEST_CASE("exception_thrown2", "[drop_disk_to_board]") {
  Board student;
  InitBoard(student);
  for (int j = 0; j < kBoardWidth; j++) {
    for (int i = 0; i < kBoardHeight; i++) {
      DropDiskToBoard(student, DiskType::kPlayer2, j);
    }
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer2, j),
                      std::runtime_error);
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////