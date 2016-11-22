#ifndef _DFA_H
#define _DFA_H

#include "./NFA.hpp"
#include <vector>

using std::vector;

/*
 * Represents a DFA state, a cached NFA state list
 */
struct DState {
  vector<State*> l;
  vector<DState*> next;
  DState *left;
  DState *right;
  DState() : next(256, NULL), left(NULL), right(NULL) {}
};

class DFA {
private:
  DState *allStates; // cached Dstate for uniqueness query
  DState *graph;
  int DList_cmp(const vector<State*> &, const vector<State*> &);
  DState* next_state(DState *d, int c);
  DState* get_DState(const vector<State*> &l);
public:
  DFA(NFA nfa);
  bool match(string input);
};

#endif
