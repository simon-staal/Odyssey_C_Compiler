#include "ast/arrays/ast_arrayInit.hpp"

ArrayInit::ArrayInit(std::vector<NodePtr> elements)
  : Node(elements)
{}

ArrayInit::~ArrayInit()
{
  for(unsigned i = 0; i < branches.size(); i++){
    delete branches[i];
  }
}

void ArrayInit::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Array Initializer [" << std::endl;
  for(unsigned i = 0; i < branches.size(); i++){
    dst << indent << i << ": " << std::endl;
    branches[i]->PrettyPrint(dst, indent+"  ");
  }
  dst << indent << "] endInitializer" << std::endl;
}

void ArrayInit::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  // Kai figure this out if you need
}

int ArrayInit::getValue(int i) const
{
  if(i < branches.size()){
    return branches[i]->getValue();
  }
  std::cerr << "Trying to getValue outside initializer range" << std::endl;
  return 0; // Default initialisation = 0
}
