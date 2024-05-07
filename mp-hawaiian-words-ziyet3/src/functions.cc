#include "functions.hpp"

#include <string>
// Your function definitions should go in this source file.

struct TwoChar {
  char cur;
  char another;
};

bool IsConsonant(char c) {
  return c == 'p' || c == 'k' || c == 'h' || c == 'l' || c == 'm' || c == 'n' ||
         c == 'w';
}

std::string ConvertConsonant(TwoChar tc) {
  char c = tc.cur;
  char prev = tc.another;
  if (c == 'w') {
    if (prev == 'i' || prev == 'e') {
      return "v";
    }
    return "w";
  }
  std::string ret = std::string(1, c);
  return ret;
}

bool IsVowel(char c) {
  return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

bool IsVowelGroup(std::string const& s) {
  return s == "ai" || s == "ae" || s == "ao" || s == "au" || s == "ei" ||
         s == "eu" || s == "iu" || s == "oi" || s == "ou" || s == "ui";
}

std::string ConvertVowelNoNext(char c) {
  if (c == 'a') {
    return "ah";
  }
  if (c == 'e') {
    return "eh";
  }
  if (c == 'i') {
    return "ee";
  }
  if (c == 'o') {
    return "oh";
  }

  return "oo";
}

std::string ConvertVowelNext(TwoChar tc) {
  char c = tc.cur;
  char next = tc.another;
  if (c == 'a') {
    if (next == 'i' || next == 'e') {
      return "eye";
    }
    return "ow";
  }

  if (c == 'e') {
    if (next == 'i') {
      return "ay";
    }
    return "eh-oo";
  }

  if (c == 'i') {
    return "ew";
  }

  if (c == 'o') {
    if (next == 'i') {
      return "oy";
    }
    return "ow";
  }

  return "ooey";
}

void DealWithVowel(std::string& res, int& idx, int len, TwoChar tc, char prev) {
  char lower_ch = tc.cur;
  char next = tc.another;
  if (idx != 0 && prev != ' ' && prev != '\'' && !IsConsonant(prev)) {
    res += '-';
  }
  if (idx + 1 == len) {
    res += ConvertVowelNoNext(lower_ch);
    idx++;
  } else {
    std::string str = std::string(1, lower_ch) + std::string(1, next);
    if (IsVowelGroup(str)) {
      TwoChar tc = {lower_ch, next};
      res += ConvertVowelNext(tc);
      idx += 2;
    } else {
      res += ConvertVowelNoNext(lower_ch);
      idx++;
    }
  }
}

std::string GetPronunc(std::string word) {
  std::string res;
  int idx = 0;
  int len = int(word.length());

  char lower_ch = char(std::tolower(word[idx]));
  if (IsConsonant(lower_ch)) {
    res += lower_ch;
    idx++;
  }

  while (idx < len) {
    lower_ch = char(std::tolower(word[idx]));
    if (IsConsonant(lower_ch)) {
      if (word[idx - 1] != ' ' && word[idx - 1] != '\'') {
        res += '-';
      }
      TwoChar tc = {lower_ch, char(std::tolower(word[idx - 1]))};
      res += ConvertConsonant(tc);
      idx++;
    } else if (IsVowel(lower_ch)) {
      TwoChar tc = {lower_ch, char(std::tolower(word[idx + 1]))};
      DealWithVowel(res, idx, len, tc, char(std::tolower(word[idx - 1])));
    } else if (lower_ch == ' ' || lower_ch == '\'') {
      res += lower_ch;
      idx++;
    } else {
      return word +
             " contains a character not a part of the Hawaiian language.";
    }
  }

  return res;
}