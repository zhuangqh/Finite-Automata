#include <iostream>
#include "./include/NFA.hpp"
#include "./include/DFA.hpp"

using std::cin;
using std::cout;
using std::endl;

int main() {
  cout << "please input a regex" << endl;
  string regex;
  cin >> regex;

  NFA nfa(regex);

  DFA dfa(nfa);
  string pattern;

  while (cin >> pattern) {
    cout << (dfa.match(pattern) ? "match" : "unmatch") << endl;
  }
}
