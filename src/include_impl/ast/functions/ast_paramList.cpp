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
    newFrame.varBindings[var] = {size, paramSize+8, -1};
    if(i < 4){
      newFrame.varBindings[var].reg = i+4; // First 4 arguments stored in registers $4-$7
      dst << "sw $" << i+4 << "," << paramSize+8 << "($30)" << std::endl; // The first 4 args aren't actually stored in the right place
    }
    paramSize += size;
  }
  if(paramSize > 16){
    newFrame.argSize = paramSize;
  }
  context.stack.push_back(newFrame);
  // std::cerr << newFrame << std::endl; // <-debugging
}
