#include "ast/ast_declarator.hpp"

// Constructors
Declarator::Declarator(NodePtr id)
{
  branches.push_back(id);
}

Declarator::Declarator(std::string id)
  : Declarator(new Identifier(id))
{}

// Destructor
Declarator::~Declarator()
{
  delete branches[0];
}

std::string Declarator::getId() const
{
  return branches[0]->getId();
}

bool Declarator::isFunction() const
{
  return false;
}

// Visualising
void Declarator::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Declarator: [" << std::endl;
  branches[0]->PrettyPrint(dst, indent+"  ");
  dst << indent << "]" << std::endl;
}
