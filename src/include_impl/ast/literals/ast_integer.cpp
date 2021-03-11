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
virtual void Integer::PrettyPrint(std::ostream &dst, std::string indent) const override
{
    dst << indent << "Integer = " << value << std::endl;
}
