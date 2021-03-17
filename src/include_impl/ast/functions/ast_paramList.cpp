#include "ast/functions/ast_paramList.hpp"
#include "ast/context.hpp" // This is for the << overload for stackFrame

void ParamList::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "ParamList [" << std::endl;
  for(unsigned i = 0; i < branches.size(); i++){
    branches[i]->PrettyPrint(dst, indent+"  ");
  }
  dst << indent << "]" << std::endl;
}

void ParamList::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  stackFrame newFrame;
  int paramSize = 0;
  for(int i = 0; i < branches.size(); i++){
    std::string var = branches[i]->getId();
    int size = branches[i]->getSize();
    paramSize += size;
    newFrame.varBindings[var] = {size, paramSize};
  }
  if(paramSize > 16){
    newFrame.argSize = paramSize;
  }
  context.stack.push_back(newFrame);
  // std::cerr << newFrame << std::endl; // <-debugging
}
