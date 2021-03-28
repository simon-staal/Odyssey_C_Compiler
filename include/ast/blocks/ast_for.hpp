#ifndef ast_for_hpp
#define ast_for_hpp

#include "ast/ast_node.hpp"

class For
  : public Node
{
public:
  // Constructor
  For(NodePtr initializer, NodePtr condition, NodePtr increment, NodePtr scope);

  // Destructor
  virtual ~For();

  // Visualising
  void PrettyPrint(std::ostream &dst, std::string indent) const override;

  // Codegen
  void generateMIPS(std::ostream &dst, Context &context, int destReg) const override;
};

#endif
