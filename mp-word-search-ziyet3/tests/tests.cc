// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Student Name                    Environment : ubuntu:bionic               //
//  Date ......: 2021/02/10                      Compiler ...: clang-10                    //
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
#include <vector>

#include "CharPositions.hpp"
#include "WordLocation.hpp"
#include "WordSearchSolver.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("search horizontal successfully", "") {
  std::vector<std::vector<char>> puzzle{{'T', 'O', 'O', 'M'},
                                        {'T', 'O', 'M', 'a'},
                                        {'c', 'k', 'l', 'd'},
                                        {'F', 's', 'R', 'B'}};

  std::string word1 = "TOM";
  WordLocation solution1 = {
      "TOM",
      std::vector<CharPositions>{CharPositions{'T', 1, 0},
                                 CharPositions{'O', 1, 1},
                                 CharPositions{'M', 1, 2}}};
  WordSearchSolver s1(puzzle);
  WordLocation l1 = s1.FindWord(word1, CheckDirection::kHorizontal);
  REQUIRE(solution1.word == l1.word);

  std::string word2 = "kld";
  WordLocation solution2 = {
      "kld",
      std::vector<CharPositions>{CharPositions{'k', 2, 1},
                                 CharPositions{'l', 2, 2},
                                 CharPositions{'d', 2, 3}}};
  WordSearchSolver s2(puzzle);
  WordLocation l2 = s2.FindWord(word2, CheckDirection::kHorizontal);
  REQUIRE(solution2.word == l2.word);
}

TEST_CASE("search horizontal failed", "") {
  std::vector<std::vector<char>> puzzle{{'T', 'O', 'O', 'M'},
                                        {'T', 'O', 'M', 'a'},
                                        {'c', 'k', 'l', 'd'},
                                        {'F', 's', 'R', 'B'}};
  std::string word1 = "OMAMA";
  WordLocation solution1 = WordLocation{};
  WordSearchSolver s1(puzzle);
  WordLocation l1 = s1.FindWord(word1, CheckDirection::kHorizontal);
  REQUIRE(solution1.word == l1.word);

  std::string word2 = "cklddt";
  WordLocation solution2 = WordLocation{};
  WordSearchSolver s2(puzzle);
  WordLocation l2 = s2.FindWord(word2, CheckDirection::kHorizontal);
  REQUIRE(solution2.word == l2.word);

  std::string word12 = "dlkc";
  WordLocation solution12 = WordLocation{};

  WordLocation l12 = s1.FindWord(word12, CheckDirection::kHorizontal);

  REQUIRE(solution12.word == l12.word);
}

TEST_CASE("search vertical successfully", "") {
  std::vector<std::vector<char>> puzzle{{'T', 'A', 'B', 'I'},
                                        {'L', 'O', 'y', 'a'},
                                        {'c', 'W', 'x', 'd'},
                                        {'T', 'U', 'k', 'K'}};

  std::string word1 = "Byx";
  WordLocation solution1 = {
      "Byx",
      std::vector<CharPositions>{CharPositions{'B', 0, 2},
                                 CharPositions{'y', 1, 2},
                                 CharPositions{'x', 2, 2}}};

  WordSearchSolver s1(puzzle);
  WordLocation l1 = s1.FindWord(word1, CheckDirection::kVertical);

  REQUIRE(solution1.word == l1.word);

  std::string word2 = "IadK";
  WordLocation solution2 = {
      "IadK",
      std::vector<CharPositions>{CharPositions{'I', 0, 3},
                                 CharPositions{'a', 1, 3},
                                 CharPositions{'d', 2, 3},
                                 CharPositions{'K', 3, 3}}};

  WordSearchSolver s2(puzzle);
  WordLocation l2 = s2.FindWord(word2, CheckDirection::kVertical);

  REQUIRE(solution2.word == l2.word);
}

TEST_CASE("search vertical failed", "") {
  std::vector<std::vector<char>> puzzle{{'T', 'A', 'B', 'I'},
                                        {'L', 'O', 'y', 'a'},
                                        {'c', 'W', 'x', 'd'},
                                        {'T', 'U', 'k', 'K'}};

  std::string word1 = "Bytt";
  WordLocation solution1 = WordLocation{};

  WordSearchSolver s1(puzzle);
  WordLocation l1 = s1.FindWord(word1, CheckDirection::kVertical);

  REQUIRE(solution1.word == l1.word);

  std::string word2 = "yxkkk";
  WordLocation solution2 = WordLocation{};

  WordSearchSolver s2(puzzle);
  WordLocation l2 = s2.FindWord(word2, CheckDirection::kVertical);

  REQUIRE(solution2.word == l2.word);

  std::string word9 = "WOA";
  WordLocation solution9 = WordLocation{};

  WordLocation l9 = s1.FindWord(word9, CheckDirection::kVertical);

  REQUIRE(solution9.word == l9.word);
}

TEST_CASE("search leftdiag successfully", "") {
  std::vector<std::vector<char>> puzzle{{'T', 'A', 'B', 'I'},
                                        {'L', 'O', 'y', 'a'},
                                        {'c', 'W', 'x', 'd'},
                                        {'T', 'U', 'k', 'K'}};
  std::string word1 = "WT";
  WordLocation solution1 = {
      "WT",
      std::vector<CharPositions>{CharPositions{'w', 2, 1},
                                 CharPositions{'T', 3, 0}}};

  WordSearchSolver s1(puzzle);
  WordLocation l1 = s1.FindWord(word1, CheckDirection::kLeftDiag);

  REQUIRE(solution1.word == l1.word);

  std::string word2 = "axU";
  WordLocation solution2 = {
      "axU",
      std::vector<CharPositions>{CharPositions{'a', 1, 3},
                                 CharPositions{'x', 2, 2},
                                 CharPositions{'U', 3, 1}}};

  WordSearchSolver s2(puzzle);
  WordLocation l2 = s2.FindWord(word2, CheckDirection::kLeftDiag);

  REQUIRE(solution2.word == l2.word);
}

TEST_CASE("search leftdiag failed", "") {
  std::vector<std::vector<char>> puzzle{{'T', 'A', 'B', 'I'},
                                        {'L', 'O', 'y', 'a'},
                                        {'c', 'W', 'x', 'd'},
                                        {'T', 'U', 'k', 'K'}};
  std::string word1 = "axw";

  WordLocation solution1 = WordLocation{};

  WordSearchSolver s1(puzzle);
  WordLocation l1 = s1.FindWord(word1, CheckDirection::kLeftDiag);

  REQUIRE(solution1.word == l1.word);

  std::string word2 = "TOxK";

  WordLocation solution2 = WordLocation{};

  WordSearchSolver s2(puzzle);
  WordLocation l2 = s2.FindWord(word2, CheckDirection::kLeftDiag);

  REQUIRE(solution2.word == l2.word);

  std::string word3 = "IyWTxg";

  WordLocation solution3 = WordLocation{};

  WordSearchSolver s3(puzzle);
  WordLocation l3 = s3.FindWord(word3, CheckDirection::kLeftDiag);

  REQUIRE(solution3.word == l3.word);

  std::string word11 = "TWyI";
  WordLocation solution11 = WordLocation{};

  WordLocation l11 = s1.FindWord(word11, CheckDirection::kLeftDiag);

  REQUIRE(solution11.word == l11.word);
}

TEST_CASE("search rightdiag successfully", "") {
  std::vector<std::vector<char>> puzzle{{'T', 'A', 'B', 'I'},
                                        {'L', 'O', 'y', 'a'},
                                        {'c', 'W', 'x', 'd'},
                                        {'T', 'U', 'k', 'K'}};

  std::string word1 = "OxK";

  WordLocation solution1 = {
      "OxK",
      std::vector<CharPositions>{CharPositions{'O', 1, 1},
                                 CharPositions{'x', 2, 2},
                                 CharPositions{'K', 3, 3}}};

  WordSearchSolver s1(puzzle);
  WordLocation l1 = s1.FindWord(word1, CheckDirection::kRightDiag);

  REQUIRE(solution1.word == l1.word);

  std::string word2 = "yd";

  WordLocation solution2 = {
      "yd",
      std::vector<CharPositions>{CharPositions{'y', 1, 2},
                                 CharPositions{'d', 2, 3}}};

  WordSearchSolver s2(puzzle);
  WordLocation l2 = s2.FindWord(word2, CheckDirection::kRightDiag);

  REQUIRE(solution2.word == l2.word);
}

TEST_CASE("search rightdiag failed", "") {
  std::vector<std::vector<char>> puzzle{{'T', 'A', 'B', 'I'},
                                        {'L', 'O', 'y', 'a'},
                                        {'c', 'W', 'x', 'd'},
                                        {'T', 'U', 'k', 'K'}};

  std::string word1 = "Oasga";
  WordLocation solution1 = WordLocation{};

  WordSearchSolver s1(puzzle);
  WordLocation l1 = s1.FindWord(word1, CheckDirection::kRightDiag);

  REQUIRE(solution1.word == l1.word);

  std::string word2 = "AOWU";
  WordLocation solution2 = WordLocation{};

  WordSearchSolver s2(puzzle);
  WordLocation l2 = s2.FindWord(word2, CheckDirection::kRightDiag);

  REQUIRE(solution2.word == l2.word);

  std::string word3 = "TOxKasd";
  WordLocation solution3 = WordLocation{};

  WordSearchSolver s3(puzzle);
  WordLocation l3 = s3.FindWord(word2, CheckDirection::kRightDiag);

  REQUIRE(solution3.word == l3.word);

  std::string word10 = "KxO";
  WordLocation solution10 = WordLocation{};

  WordLocation l10 = s1.FindWord(word10, CheckDirection::kRightDiag);

  REQUIRE(solution10.word == l10.word);
}

TEST_CASE("search all direction", "") {
  std::vector<std::vector<char>> puzzle{{'T', 'A', 'B', 'I'},
                                        {'L', 'O', 'y', 'a'},
                                        {'c', 'W', 'x', 'd'},
                                        {'T', 'U', 'k', 'K'}};

  WordSearchSolver s(puzzle);

  std::string word1 = "yWT";

  WordLocation solution1 = {
      "yWT",
      std::vector<CharPositions>{CharPositions{'y', 1, 2},
                                 CharPositions{'W', 2, 1},
                                 CharPositions{'T', 3, 0}}};

  WordLocation l1 = s.FindWord(word1);

  REQUIRE(solution1.word == l1.word);

  std::string word2 = "Byxk";
  WordLocation solution2 = {
      "Byxk",
      std::vector<CharPositions>{CharPositions{'B', 0, 2},
                                 CharPositions{'y', 1, 2},
                                 CharPositions{'x', 2, 2},
                                 CharPositions{'k', 3, 2}}};

  WordLocation l2 = s.FindWord(word2);

  REQUIRE(solution2.word == l2.word);

  std::string word3 = "UkK";
  WordLocation solution3 = {
      "UkK",
      std::vector<CharPositions>{CharPositions{'U', 3, 1},
                                 CharPositions{'k', 3, 2},
                                 CharPositions{'K', 3, 3}}};

  WordLocation l3 = s.FindWord(word3);

  REQUIRE(solution3.word == l3.word);

  std::string word4 = "TOxK";
  WordLocation solution4 = {
      "TOxK",
      std::vector<CharPositions>{CharPositions{'T', 0, 0},
                                 CharPositions{'O', 1, 1},
                                 CharPositions{'x', 2, 2},
                                 CharPositions{'K', 3, 3}}};

  WordLocation l4 = s.FindWord(word4);

  REQUIRE(solution4.word == l4.word);

  std::string word5 = "TOxKj";
  WordLocation solution5 = WordLocation{};

  WordLocation l5 = s.FindWord(word5);

  REQUIRE(solution5.word == l5.word);

  std::string word6 = "yxkK";
  WordLocation solution6 = WordLocation{};

  WordLocation l6 = s.FindWord(word6);

  REQUIRE(solution6.word == l6.word);

  std::string word7 = "xUWT";
  WordLocation solution7 = WordLocation{};

  WordLocation l7 = s.FindWord(word7);

  REQUIRE(solution7.word == l7.word);

  std::string word8 = "LOyae";
  WordLocation solution8 = WordLocation{};

  WordLocation l8 = s.FindWord(word8);

  REQUIRE(solution8.word == l8.word);

  std::string word9 = "WOA";
  WordLocation solution9 = WordLocation{};

  WordLocation l9 = s.FindWord(word9);

  REQUIRE(solution9.word == l9.word);

  std::string word10 = "KxO";
  WordLocation solution10 = WordLocation{};

  WordLocation l10 = s.FindWord(word10);

  REQUIRE(solution10.word == l10.word);

  std::string word11 = "TWyI";
  WordLocation solution11 = WordLocation{};

  WordLocation l11 = s.FindWord(word11);

  REQUIRE(solution11.word == l11.word);

  std::string word12 = "dxWc";
  WordLocation solution12 = WordLocation{};

  WordLocation l12 = s.FindWord(word12);

  REQUIRE(solution12.word == l12.word);
}
/////////////////////////////////////////////////////////////////////////////////////////////