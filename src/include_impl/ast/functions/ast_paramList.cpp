#include "ast/functions/ast_paramList.hpp"

void ParamList::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "ParamList [" << std::endl;
  for(unsigned i = 0; i < branches.size(); i++){
    branches[i]->PrettyPrint(dst, indent+"  ");
  }
  dst << indent << "]" << std::endl;
}
