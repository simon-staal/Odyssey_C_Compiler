#include "ast/ast_pointerDeclarator.hpp"

// Constructors
PointerDeclarator::PointerDeclarator(NodePtr id)
{
  branches.push_back(id);
}

// Destructor
PointerDeclarator::~PointerDeclarator()
{
  delete branches[0];
}

// Visualising
void PointerDeclarator::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Pointer Declarator [" << std::endl;
  dst << indent << "Identifier: " << std::endl;
  branches[0]->PrettyPrint(dst, indent+"  ");
  dst << indent << "]" << std::endl;
}

// Codegen helpers
std::string PointerDeclarator::getId() const
{
  return branches[0]->getId();
}

bool PointerDeclarator::isInit() const
{
  return false;
}

bool PointerDeclarator::isFunction() const
{
  return false;
}

bool PointerDeclarator::isPtr() const
{
  return true;
}
