#include "ast/ast_initDeclarator.hpp"

// Constructor
InitDeclarator::InitDeclarator(NodePtr declarator, NodePtr initializer)
{
  branches.push_back(declarator);
  branches.push_back(initializer);
}

// Destructor
InitDeclarator::~InitDeclarator()
{
  delete branches[0];
  delete branches[1];
}

// Visualising
void InitDeclarator::PrettyPrint(std::ostream &dst, std::string indent) const
{
  branches[0]->PrettyPrint(dst, indent);
  dst << indent << "Initializer : [" << std::endl;
  branches[1]->PrettyPrint(dst, indent+"  ");
  dst << indent << "]" << std::endl;
}

// Codegen (could probably refactor into here if necessary -- will do later)
void InitDeclarator::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  branches[1]->generateMIPS(dst, context, destReg);
}

// Helpers
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

int InitDeclarator::getValue() const
{
  return branches[1]->getValue();
}
