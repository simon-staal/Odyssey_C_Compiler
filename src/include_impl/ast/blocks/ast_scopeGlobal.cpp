#include "ast/blocks/ast_scopeGlobal.hpp"

// Visualising
void GlobalScope::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Global Scope [" << std::endl;
  for(unsigned i = 0; i < branches.size(); i++){
    branches[i]->PrettyPrint(dst, indent+"  ");
  }
  dst << indent << "]" << std::endl;
}

// Codegen
void GlobalScope::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  for(unsigned i = 0; i < branches.size(); i++){
    branches[i]->generateMIPS(dst, context, destReg);
  }
}
