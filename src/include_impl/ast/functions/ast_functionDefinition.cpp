#include "ast/functions/ast_functionDefinition.hpp"

// Constructors
FunctionDefinition::FunctionDefinition(NodePtr declaration, NodePtr scope)
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

// Visualising
void FunctionDefinition::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Function Definition [" << std::endl;
  branches[0]->PrettyPrint(dst, indent+"  ");
  branches[1]->PrettyPrint(dst, indent+"  ");
  dst << indent << "]" << std::endl;
}

// Codegen
void FunctionDefinition::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  NodePtr funcDec = branches[0]->getNode(1);
  funcDec->generateMIPS(dst, context, destReg);
  // At this point, $sp and $fp should be pointing at the right place
  // All params are assigned in current.varBindings, and will copied by the function call
  branches[1]->generateMIPS(dst, context, destReg);
}

bool FunctionDefinition::isFunction() const
{
  return true;
}
