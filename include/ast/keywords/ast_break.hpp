#ifndef ast_break_hpp
#define ast_break_hpp

#include "ast/ast_node.hpp"

class Break
  : public Node
{
public:
  // Should inherit constructor from Node()

  // Visualising
  void PrettyPrint(std::ostream &dst, std::string indent) const override;

  // Codegen
  void generateMIPS(std::ostream &dst, Context &context, int destReg) const override;
};

#endif
