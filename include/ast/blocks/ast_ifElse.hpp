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

  // Where things should be
  NodePtr getCondition() const;
  NodePtr getIfScope() const;
  NodePtr getElseScope() const;

  // Visualising
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;

  virtual void generateMIPS(std::ostream &dst, Context &context, int destReg) const override;
};

#endif
