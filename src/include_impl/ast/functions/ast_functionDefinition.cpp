#include "ast/functions/ast_functionDefinition.hpp"

// Constructors
FunctionDefinition::FunctionDefinition(NodePtr declaration, NodePtr scope) //<- tempted to change type of scope to ScopePtr but then i'd have to include the hpp
{
  branches.push_back(declaration);
  branches.push_back(scope);
}

// Destructor
FunctionDefinition::~FunctionDefinition()
{
  delete branches[0];
  delete branches[1];
}

// Where stuff is
NodePtr FunctionDefinition::getDeclaration() const
{
  return branches[0];
}

NodePtr FunctionDefinition::getScope() const
{
  return branches[1];
}

// Visualising
void FunctionDefinition::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Function Definition [" << std::endl;
  branches[0]->PrettyPrint(dst, indent+"  ");
  branches[1]->PrettyPrint(dst, indent+"  ");
  dst << indent << "]" << std::endl;
}
