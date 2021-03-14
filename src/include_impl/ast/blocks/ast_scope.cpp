#include "ast/blocks/ast_scope.hpp"

// Just in case we need it
std::vector<NodePtr> Scope::getScope()
{
  return branches;
}

// Visualising
void Scope::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Scope [" << std::endl;
  for(unsigned i = 0; i < branches.size(); i++){
    branches[i]->PrettyPrint(dst, indent+"  ");
  }
  dst << indent << "]" << std::endl;
}
