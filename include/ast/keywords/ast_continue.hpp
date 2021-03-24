#ifndef ast_continue_hpp
#define ast_continue_hpp

#include "ast/ast_node.hpp"

class Continue
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
