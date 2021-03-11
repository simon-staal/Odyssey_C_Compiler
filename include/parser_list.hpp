#ifndef parser_list_hpp
#define parser_list_hpp

#include "ast/ast_node.hpp"

#include <vector>

// Functions to be used in parser for instantiation / concatenation
typedef std::vector<NodePtr> List;
typedef List *ListPtr;

inline ListPtr initList(NodePtr expr);

inline ListPtr concatList(ListPtr exprList, NodePtr expr);

#endif
