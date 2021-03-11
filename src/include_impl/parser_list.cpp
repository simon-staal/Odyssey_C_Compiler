#include "parser_list.hpp"

// Functions to be used in parser for instantiation / concatenation
inline ListPtr initList(NodePtr expr)
{
  ListPtr exprList = new List(); // Potentially replace with Nodelist(NodePtr) constructor
  exprList->push_back(expr);
  return exprList;
}

inline ListPtr concatList(ListPtr exprList, NodePtr expr)
{
  exprList->push_back(expr);
  return exprList;
}
