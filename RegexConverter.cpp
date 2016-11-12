#include "./RegexConverter.hpp"

map<char, int> RegexConverter::precedenceMap = {
  {'(', 1}, {'|', 2}, {'.', 3}, {'?', 4}, {'*', 4}, {'+', 4}, {'^', 5}
};

int RegexConverter::getPrecedence(char c) {
  if (precedenceMap.find(c) != precedenceMap.end()) {
    return precedenceMap[c];
  } else {
    return 6;
  }
}

string RegexConverter::formatRegex(string regex) {
  string res;
  string allOperators = "|?+*^";
  string binaryOperators = "^|";

  for (size_t i = 0; i < regex.size(); ++i) {
    char c1 = regex[i];

    if (i + 1 < regex.size()) {
      char c2 = regex[i + 1];

      res += c1;
      if (c1 != '(' && c2 != ')' && allOperators.find(c2) == -1 && binaryOperators.find(c1) == -1) {
        res += '.';
      }
    } else {
      res += regex[i];
    }
  }

  return res;
}

string RegexConverter::getPostfix(string regex) {
  string postfix;

  stack<char> s;

  string infix = formatRegex(regex);

  for (auto c : infix) {
    switch (c) {
    case '(':
      s.push(c);
      break;
    case ')':
      while (s.top() != '(') {
        postfix += s.top();
        s.pop();
      }
      s.pop();
      break;
    default:
      while (s.size()) {
        char topChar = s.top();
        int topCharPrecedence = getPrecedence(topChar);
        int curPrecedence = getPrecedence(c);

        if (topCharPrecedence >= curPrecedence) {
          postfix += s.top();
          s.pop();
        } else {
          break;
        }
      }
      s.push(c);
      break;
    }
  }

  while (s.size()) {
    postfix += s.top();
    s.pop();
  }

  return postfix;
}
