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
  bool match(const string &s);
};

#endif
