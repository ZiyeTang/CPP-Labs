#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

// Your function declarations should go in this header file.
#include <string>
std::string GetPronunc(std::string word);
bool IsConsonant(char c);
std::string ConvertConsonant(char c, char prev);
bool IsVowel(char c);
bool IsVowelGroup(std::string const& s);
std::string ConvertVowel(char c);
std::string ConvertVowelNext(char c, char next);
#endif