#ifndef _REGEX_CONVERTER_H
#define _REGEX_CONVERTER_H

#include <map>
#include <string>
#include <stack>

using std::map;
using std::string;
using std::stack;

class RegexConverter {
private:
  static map<char, int> precedenceMap;
  string formatRegex(string regex);
  int getPrecedence(char c);
public:
  RegexConverter() {}

  string getPostfix(string regex);
};

#endif
