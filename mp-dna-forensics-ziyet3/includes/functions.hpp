#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "utilities.hpp"
struct PatternStr {
  std::string pattern;
  std::string str;
};
std::string Match(std::vector<std::vector<std::string>> const& data,
                  std::string const& str);
std::vector<int> CountPatterns(std::vector<std::string> const& patterns,
                               std::string const& str);

int LongestConsec(PatternStr const& arg);

#endif