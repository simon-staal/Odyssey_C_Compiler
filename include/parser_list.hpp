#ifndef parser_list_hpp
#define parser_list_hpp

#include "ast/ast_node.hpp"

#include <vector>

// Functions to be used in parser for instantiation / concatenation
typedef std::vector<NodePtr> List;
typedef List *ListPtr;

inline NodeListPtr initList(NodePtr expr)
{
  NodeListPtr exprList = new List(); // Potentially replace with Nodelist(NodePtr) constructor
  exprList->push_back(expr);
  return exprList;
}

inline NodeListPtr concatList(ListPtr exprList, NodePtr expr)
{
  exprList->push_back(expr);
  return exprList;
}

#endif
