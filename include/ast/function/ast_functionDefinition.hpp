#ifndef ast_functionDefinition_hpp
#define ast_functionDefinition_hpp

#include "ast_node.hpp"

// Represents a function as a declaration + {shit in here}, where the scope node contains the shit

class FunctionDefinition
  : public Node
{
  // Constructors
  FunctionDefinition(NodePtr declaration, NodePtr scope) //<- tempted to change type of scope to ScopePtr but then i'd have to include the hpp
  {
    branches.push_back(declaration);
    branches.push_back(scope);
  }

  // Destructor
  virtual ~FunctionDefinition()
  {
    delete branches[0];
    delete branches[1];
  }

  // Where stuff is
  NodePtr getDeclaration() const
  {
    return branches[0];
  }

  NodePtr getScope() const
  {
    return branches[1];
  }

  // Visualising
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override
  {
    dst << indent << "Function Definition[" << std::endl;
    branches[0]->PrettyPrint(dst, indent+"  ");
    branches[1]->PrettyPrint(dst, indent+"  ");
    dst << indent << "]" << std::endl;
  }
};

#endif
