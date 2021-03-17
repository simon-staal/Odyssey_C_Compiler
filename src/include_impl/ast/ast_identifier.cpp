#include "ast/ast_identifier.hpp"

// Constructor
Identifier::Identifier(std::string _id)
  : id(_id)
{}

// Getting identifier
std::string Identifier::getId() const
{
  if(branches.empty()) { return id; }
  else{ return branches[0]->getId(); }
}

// Visualising
void Identifier::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Identifier: " << id << std::endl;
}

void Identifier::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  // only if declarator for variable
  // context.stack.back().varBindings[id] = {0, 0};
}
