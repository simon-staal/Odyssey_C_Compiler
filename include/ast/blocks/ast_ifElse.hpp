#ifndef ast_ifElse_hpp
#define ast_ifElse_hpp

#include "ast/ast_node.hpp"
#include "ast/blocks/ast_scope.hpp" // Required for exclusive if constructor

class IfElse
  : public Node
{
public:
  // Constructors
  IfElse(NodePtr condition, NodePtr ifScope, NodePtr elseScope);
  IfElse(NodePtr condition, NodePtr ifScope);

  // Destructor
  virtual ~IfElse();

  // Visualising
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;

  // Codegen
  virtual void generateMIPS(std::ostream &dst, Context &context, int destReg) const override;
};

#endif
