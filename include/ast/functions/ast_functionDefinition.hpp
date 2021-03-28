#ifndef ast_functionDefinition_hpp
#define ast_functionDefinition_hpp

#include "ast/ast_node.hpp"

// Represents a function as a declaration + {shit in here}, where the scope node contains the shit

class FunctionDefinition
  : public Node
{
public:
  // Constructors
  FunctionDefinition(NodePtr declaration, NodePtr scope);

  // Destructor
  virtual ~FunctionDefinition();

  // Visualising
  void PrettyPrint(std::ostream &dst, std::string indent) const override;

  // Codegen + helpers
  void generateMIPS(std::ostream &dst, Context &context, int destReg) const override;
  bool isFunction() const override;
};

#endif
