#include "functions.hpp"

#include <iostream>
std::string Match(std::vector<std::vector<std::string>> const& data,
                  std::string const& str) {
  std::vector<int> num_patterns = CountPatterns(data[0], str);
  for (int i = 1; i < int(data.size()); i++) {
    bool flag = true;
    for (int j = 1; j < int(data[i].size()); j++) {
      if (num_patterns[j - 1] != std::stoi(data[i][j])) {
        flag = false;
        break;
      }
    }
    if (flag) {
      return data[i][0];
    }
  }
  return "No match";
}

std::vector<int> CountPatterns(std::vector<std::string> const& patterns,
                               std::string const& str) {
  std::vector<int> num_patterns;
  for (int i = 1; i < int(patterns.size()); i++) {
    PatternStr ps = {patterns[i], str};
    num_patterns.push_back(LongestConsec(ps));
  }
  return num_patterns;
}

int LongestConsec(PatternStr const& arg) {
  int longest = 0;
  std::string pattern = arg.pattern;
  std::string str = arg.str;
  int strlen = int(str.length());
  int patlen = int(pattern.length());

  for (int i = 0; i < strlen; i++) {
    int count = 0;
    bool flag = true;
    int j = i;
    while (flag) {
      for (int k = 0; k < patlen; k++) {
        if (j + k >= strlen || str[j + k] != pattern[k]) {
          flag = false;
          break;
        }
      }

      j += patlen;

      if (flag) {
        count++;
      }
    }
    if (longest < count) {
      longest = count;
    }
  }
  return longest;
}
