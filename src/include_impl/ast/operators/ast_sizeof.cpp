#include "ast/operators/ast_sizeof.hpp"

// Constructor
SizeOf::SizeOf(NodePtr type)
{
  branches.push_back(type);
}

SizeOf::~SizeOf()
{
  branches[0];
}

void SizeOf::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "sizeof [" << std::endl;
  branches[0]->PrettyPrint(dst, indent+"  ");
  dst << indent << "]" << std::endl;
}

void SizeOf::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  int size = branches[0]->getSize();
  if(size != 0){
    dst << "li $" << destReg << "," << size << std::endl;
  }
  else{
    dst << "li $" << destReg << "," << branches[0]->getSize(context) << std::endl;
  }
}
