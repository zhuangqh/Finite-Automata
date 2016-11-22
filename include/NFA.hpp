#ifndef _NFA_H
#define _NFA_H

#include <vector>
#include <string>
#include "./Fragment.hpp"

using std::vector;
using std::string;


class NFA {
private:
  State *graph;
public:
  NFA(string);
  static void addState(vector<State*> &l, State *s);
  static void step(vector<State*> &cur, int c, vector<State*> &next);
  static bool is_match(const vector<State*> &l);
  State* get_graph();
  bool match(const string &s);
};

#endif
