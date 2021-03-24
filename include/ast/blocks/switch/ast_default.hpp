#ifndef ast_default_hpp
#define ast_default_hpp

#include "ast/ast_node.hpp"

class Default
  : public Node
{
  // Constructor
  Default(NodePtr execute);

  // Destructor
  virtual ~Default();

  // Visualising
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;

  // Codegen
  virtual void generateMIPS(std::ostream &dst, Context &context, int destReg) const override;
};

#endif
