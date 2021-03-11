#include "ast/ast_identifier.hpp"

// Constructor
Identifier::Identifier(std::string _id)
  : id(_id)
{}

// Getting identifier
std::string Identifier::getId() const
{
  return id;
}

// Visualising
void Identifier::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Identifier: " << id << std::endl;
}
