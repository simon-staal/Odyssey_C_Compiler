#ifndef ast_switch_hpp
#define ast_switch_hpp

#include "ast/ast_node.hpp"

class Switch
  : public Node
{
public:
  // Constructor
  Switch(NodePtr expression, NodePtr scope);

  // Destructor
  virtual ~Switch();

  // Visualising
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;

  // Codegen
  virtual void generateMIPS(std::ostream &dst, Context &context, int destReg) const override;
};

#endif
