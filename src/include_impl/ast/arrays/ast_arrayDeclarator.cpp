#include "ast/arrays/ast_arrayDeclarator.hpp"

// Constructors
ArrayDeclarator::ArrayDeclarator(NodePtr id, NodePtr size)
{
  branches.push_back(id);
  branches.push_back(size);
}


ArrayDeclarator::ArrayDeclarator(NodePtr id)
  : ArrayDeclarator(id, new Integer(-1))
{

}

// Destructor
ArrayDeclarator::~ArrayDeclarator()
{
  delete branches[0];
  delete branches[1];
}

// Visualising
void ArrayDeclarator::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Array Declarator [" << std::endl;
  dst << indent << "Identifier: " << std::endl;
  branches[0]->PrettyPrint(dst, indent+"  ");
  dst << indent << "Size: " << std::endl;
  branches[1]->PrettyPrint(dst, indent+"  ");
  dst << indent << "]" << std::endl;
}

// Codegen helpers
std::string ArrayDeclarator::getId() const
{
  return branches[0]->getId();
}

bool ArrayDeclarator::isInit() const
{
  return false;
}

bool ArrayDeclarator::isFunction() const
{
  return false;
}

int ArrayDeclarator::getArraySize() const // gets size of array when its being declared
{
  return branches[1]->getValue();
}
