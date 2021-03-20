#include "ast/ast_initDeclarator.hpp"

InitDeclarator::InitDeclarator(NodePtr declarator, NodePtr initializer)
{
  branches.push_back(declarator);
  branches.push_back(initializer);
}

InitDeclarator::~InitDeclarator()
{
  delete branches[0];
  delete branches[1];
}

std::string InitDeclarator::getId() const
{
  return branches[0]->getId();
}

bool InitDeclarator::isFunction() const
{
  return branches[0]->isFunction();
}

bool InitDeclarator::isInit() const
{
  return true;
}

void InitDeclarator::PrettyPrint(std::ostream &dst, std::string indent) const
{
  branches[0]->PrettyPrint(dst, indent);
  dst << indent << "Initializer : [" << std::endl;
  branches[1]->PrettyPrint(dst, indent+"  ");
  dst << indent << "]" << std::endl;
}

void InitDeclarator::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  branches[1]->generateMIPS(dst, context, destReg);
}
