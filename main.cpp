#include <iostream>
#include "./include/NFA.hpp"

using std::cin;
using std::cout;
using std::endl;

int main() {
  cout << "please input a regex" << endl;
  string regex;
  cin >> regex;

  NFA nfa(regex);

  string pattern;

  while (cin >> pattern) {
    cout << (nfa.match(pattern) ? "match" : "unmatch") << endl;
  }
}
