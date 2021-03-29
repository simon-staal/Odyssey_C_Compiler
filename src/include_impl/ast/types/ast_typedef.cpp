#include "ast/types/ast_typedef.hpp"

// This was never really implemented properly, we'd need to add an extern mapping in the lexer / parser to update types as we go

// Constructor
TypeDef::TypeDef(NodePtr type)
{
  branches.push_back(type);
}

// Destructor
TypeDef::~TypeDef()
{
  delete branches[0];
}

// Visualising
void TypeDef::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << "Typedef: ";
  branches[0]->PrettyPrint(dst, indent);
}
