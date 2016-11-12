#ifndef _FRAGMENT_H
#define _FRAGMENT_H

#include <vector>
#include <iostream>

using std::vector;
using std::ostream;

enum {
  MATCH = 256,
	SPLIT = 257
};

struct State {
  int c;
  State *out1;
  State *out2;
  State(int cc, State *out11 = nullptr, State *out22 = nullptr) : c(cc), out1(out11), out2(out22) {};
  void print() {
    std::cout << " [" << c << "](" << (out1 ? out1->c : 0)
              << ")(" << (out2 ? out2->c : 0) << ") ";
  }
};

struct Fragment {
  State *start;
  vector<State*> end;
  Fragment(State *s) : start(s) {}

  void addEnd(State *s) {
    end.push_back(s);
  }

  void patch(State *s, bool isConcat) {
    if (isConcat) {
      for (auto e : end) {
        e->out1 = s;
      }
    } else {
      for (auto e : end) {
        e->out2 = s; // another path
      }
    }
  }

  static Fragment* concat(State *s, Fragment *e1, Fragment *e2) {
    auto f = new Fragment(s);
    auto ends = e1->end;
    if (e2)
      ends.insert(e1->end.end(), e2->end.begin(), e2->end.end());
    f->end = ends;
    return f;
  }
};

#endif
