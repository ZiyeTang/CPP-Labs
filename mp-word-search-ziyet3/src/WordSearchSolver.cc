#include "WordSearchSolver.hpp"

WordSearchSolver::WordSearchSolver(
    const std::vector<std::vector<char>>& puzzle) {
  puzzle_height_ = puzzle.size();
  puzzle_width_ = puzzle[0].size();
  std::vector<char> row(puzzle_width_);
  for (size_t i = 0; i < puzzle_height_; i++) {
    for (size_t j = 0; j < puzzle_width_; j++) {
      row[j] = puzzle[i][j];
    }
    puzzle_.push_back(row);
  }
}

bool WordSearchSolver::LocationInBounds(size_t row, size_t col) const {
  return ((row < puzzle_height_) && (col < puzzle_width_));
}

WordLocation WordSearchSolver::FindWord(const std::string& word,
                                        CheckDirection direction) {
  int changes[4][2] = {{0, 1}, {1, 0}, {1, -1}, {1, 1}};
  int rc = changes[int(direction)][0];
  int cc = changes[int(direction)][1];
  int wordlen = int(word.length());
  std::vector<CharPositions> char_pos;
  for (size_t i = 0; i < puzzle_height_; i++) {
    for (size_t j = 0; j < puzzle_width_; j++) {
      size_t r = i;
      size_t c = j;
      int start = 0;

      while (start < wordlen && LocationInBounds(r, c)) {
        if (puzzle_[r][c] != word[start]) {
          break;
        }
        char_pos.push_back(CharPositions{puzzle_[r][c], size_t(r), size_t(c)});
        r += rc;
        c += cc;
        start++;
      }

      if (start == wordlen) {
        return WordLocation{word, char_pos};
      }

      char_pos.clear();
    }
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::FindWord(const std::string& word) {
  WordLocation l1 = FindWord(word, CheckDirection::kHorizontal);
  if (!(l1.word.empty())) {
    return l1;
  }

  WordLocation l2 = FindWord(word, CheckDirection::kVertical);
  if (!(l2.word.empty())) {
    return l2;
  }

  WordLocation l3 = FindWord(word, CheckDirection::kLeftDiag);
  if (!(l3.word.empty())) {
    return l3;
  }

  WordLocation l4 = FindWord(word, CheckDirection::kRightDiag);
  if (!(l4.word.empty())) {
    return l4;
  }

  return WordLocation{};
}
