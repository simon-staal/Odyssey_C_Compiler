#include "ast/literals/ast_integer.hpp"

// Constructor
Integer::Integer(int _value)
  : value(_value)
{}

Integer::Integer() // Default initializer
  : Integer(0)
{}

// Useful shit (probs)
int Integer::getValue() const
{
  return value;
}

// Visualising
void Integer::PrettyPrint(std::ostream &dst, std::string indent) const 
{
    dst << indent << "Integer = " << value << std::endl;
}

void generateMIPS(std::ostream &dst, Context context, int destReg) const
{
  dst << "li $" << destReg << ", " << getValue() << std::endl;
}
