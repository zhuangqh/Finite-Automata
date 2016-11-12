#include "./NFA.hpp"
#include "./RegexConverter.hpp"
#include <stack>
#include <iostream>

#define _DEBUG

using std::string;
using std::stack;

NFA::NFA(string str) {
  RegexConverter r;
  string postfix = r.getPostfix(str);
  stack<Fragment*> sf;

#ifdef _DEBUG
  std::cout << "postfix " << postfix << std::endl;
#endif

  State *s;
  Fragment *e1, *e2, *f;
  vector<State*> ends;

  for (auto c : postfix) {
    switch(c) {
    case '.': // catenate
      e2 = sf.top();
      sf.pop();
      e1 = sf.top();
      sf.pop();

      e1->patch(e2->start, true);
      sf.push(Fragment::concat(e1->start, e2, nullptr));
      break;
    case '|': // alternate
      e2 = sf.top();
      sf.pop();
      e1 = sf.top();
      sf.pop();

      s = new State(SPLIT, e1->start, e2->start);
      sf.push(Fragment::concat(s, e1, e2));
      break;
    case '?': // zero or one
      e1 = sf.top();
      sf.pop();

      s = new State(SPLIT, nullptr, e1->start);
      f = Fragment::concat(s, e1, nullptr);
      f->addEnd(s); // zero exit
      sf.push(f);
      break;
    case '*': // zero or more
      e1 = sf.top();
      sf.pop();

      s = new State(SPLIT, nullptr, e1->start);
      e1->patch(s, false);
      f = new Fragment(s);
      f->addEnd(s); // zero exit
      sf.push(f);
      break;
    case '+': // one or more
      e1 = sf.top();
      sf.pop();

      s = new State(SPLIT, nullptr, e1->start);
      e1->patch(s, false);
      f = Fragment::concat(s, e1, nullptr);
      sf.push(f);
      break;
    default:
      s = new State(c);
      f = new Fragment(s);
      f->addEnd(s);
      sf.push(f);
      break;
    }
  }

  e1 = sf.top();
  e1->patch(new State(MATCH), true);
  graph = e1->start;
}

void addState(vector<State*> &l, State *s) {
  if (s == nullptr) return;

  if (s->c == SPLIT) {
    addState(l, s->out1);
    addState(l, s->out2);
  } else {
    l.push_back(s);
  }
}

void step(vector<State*> &curList, int c, vector<State*> &nextList) {
  for (auto state : curList) {
    if (state->c == c) {
      addState(nextList, state->out1);
      addState(nextList, state->out2);
    }
  }
  curList = nextList;
  nextList.clear();
}

bool is_match(const vector<State*> &l) {
  for (auto state : l) {
    if (state->c == MATCH)
      return true;
  }
  return false;
}

void print(vector<State*> a) {
  for (auto s : a) {
    s->print();
  }
  std::cout << std::endl;
}

bool NFA::match(const string &s) {
  vector<State*> curList, nextList;

  addState(curList, graph);

#ifdef _DEBUG
  print(curList);
#endif

  for (auto c : s) {
    step(curList, c, nextList);
#ifdef _DEBUG
    print(curList);
#endif
  }

  return is_match(curList);
}
