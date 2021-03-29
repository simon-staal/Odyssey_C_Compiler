#include "ast/literals/ast_char.hpp"

// Constructor
Char::Char(int _value)
  : value(_value)
{}

// Visualising
void Char::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Char = '" << (char)value << "'" << std::endl;
}

// Codegen
void Char::generateTypeMIPS(std::ostream &dst, Context &context, int destReg, enum Specifier type) const
{
  dst << "li $" << destReg << "," << value << std::endl;
}

int Char::getValue() const
{
  return value;
}

int Char::getSize() const
{
  return 1;
}
