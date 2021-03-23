#include "ast/blocks/ast_scope.hpp"

// Visualising
void Scope::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Scope [" << std::endl;
  for(unsigned i = 0; i < branches.size(); i++){
    branches[i]->PrettyPrint(dst, indent+"  ");
  }
  dst << indent << "]" << std::endl;
}

// Codegen
void Scope::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  context.enterScope();
  for(unsigned i = 0; i < branches.size(); i++){
    branches[i]->generateMIPS(dst, context, destReg);
  }
  context.exitScope(dst);
}
