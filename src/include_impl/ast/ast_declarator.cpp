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
virtual Declarator::~Declarator()
{
  delete branches[0];
}

// Where stuff is
NodePtr Declarator::getId() const
{
  return branches[0];
}

// Visualising
virtual void Declarator::PrettyPrint(std::ostream &dst, std::string indent) const override
{
  dst << indent << "Declarator: [" << std::endl;
  branches[0]->PrettyPrint(dst, indent+"  ");
  dst << indent << "]" << std::endl;
}
