#include "ast/blocks/ast_ifElse.hpp"

// Constructors
IfElse::IfElse(NodePtr condition, NodePtr ifScope, NodePtr elseScope)
{
  branches.push_back(condition);
  branches.push_back(ifScope);
  branches.push_back(elseScope);
}

IfElse::IfElse(NodePtr condition, NodePtr ifScope)
  : IfElse(condition, ifScope, new Scope())
{}

// Destructor
IfElse::~IfElse()
{
  delete branches[0];
  delete branches[1];
  delete branches[2];
}

// Where things should be
NodePtr IfElse::getCondition() const
{
  return branches[0];
}

NodePtr IfElse::getIfScope() const
{
  return branches[1];
}

NodePtr IfElse::getElseScope() const
{
  return branches[2];
}

// Visualising
void IfElse::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Condition [" << std::endl;
  branches[0]->PrettyPrint(dst, indent+"  ");
  dst << indent << "] endCondition" << std::endl;
  dst << indent << "If Scope [" << std::endl;
  branches[1]->PrettyPrint(dst, indent+"  ");
  dst << indent << "] endIfScope" << std::endl;
  dst << indent << "Else Scope [" << std::endl;
  branches[2]->PrettyPrint(dst, indent+"  ");
  dst << indent << "] endElseScope" << std::endl;
}
