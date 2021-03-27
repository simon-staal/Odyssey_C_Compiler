#ifndef ast_empty_hpp
#define ast_empty_hpp

#include "ast_node.hpp"

// Symbolises empty node, used in parser for For loops

class EmptyNode
  : public Node
{
public:
  // Should inherit contructor from Node

  // Visualising
  void PrettyPrint(std::ostream &dst, std::string indent) const override;

  // Codegen
  void generateMIPS(std::ostream &dst, Context &context, int destReg) const override {} // Does nothing (duh)
};

#endif
