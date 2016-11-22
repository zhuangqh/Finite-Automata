#include "../include/DFA.hpp"
#include <algorithm>

DState* DFA::get_DState(const vector<State*> &l) {
  DState *ptr = allStates, **next = NULL;

  int order;
  vector<State*> sortedList = l;
  std::sort(sortedList.begin(), sortedList.end(), [](State* a, State* b) { return a->c < b->c; });
  while (ptr) {
    order = DList_cmp(sortedList, ptr->l);
    if (order < 0) {
      next = &(ptr->left);
    } else if (order > 0) {
      next = &(ptr->right);
    } else {
      return ptr;
    }

    if (!next) {
      *next = new DState();
      (*next)->l = sortedList;
      return *next;
    }
  }

  // when root pointer is NULL
  ptr = new DState();
  ptr->l = sortedList;
  return ptr;
}

int DFA::DList_cmp(const vector<State*> &l1, const vector<State*> &l2) {
  if (l1.size() < l2.size()) return -1;
  if (l1.size() > l2.size()) return 1;

  for (size_t i = 0; i < l1.size(); ++i) {
    if (l1[i] < l2[i]) return -1;
    if (l1[i] > l2[i]) return 1;
  }
  return 0;
}

DState* DFA::next_state(DState *d, int c) {
  vector<State*> nextList;
  NFA::step(d->l, c, nextList);
  return (d->next[c] = get_DState(nextList));
}

DFA::DFA(NFA nfa) {
  vector<State*> nextList;
  NFA::addState(nextList, nfa.get_graph());
  graph = get_DState(nextList);
}

bool DFA::match(string input) {
  DState *next, *p;
  p = graph;
  for (auto c : input) {
    if ((next = p->next[c]) == NULL) {
      next = next_state(p, c);
    }
    p = next;
  }

  return NFA::is_match(p->l);
}
