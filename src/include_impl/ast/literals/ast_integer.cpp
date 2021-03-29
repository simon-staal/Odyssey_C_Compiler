#include "ast/literals/ast_integer.hpp"

// Constructor
Integer::Integer(int _value)
  : value(_value)
{}

Integer::Integer() // Default initializer
  : Integer(0)
{}

// Visualising
void Integer::PrettyPrint(std::ostream &dst, std::string indent) const
{
    dst << indent << "Integer = " << value << std::endl;
}

// Codegen
void Integer::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  dst << "li $" << destReg << "," << value << std::endl;
}

int Integer::getValue() const // returns value
{
  return value;
}

int Integer::getSize() const
{
  return 4; // Int size is 4
}
