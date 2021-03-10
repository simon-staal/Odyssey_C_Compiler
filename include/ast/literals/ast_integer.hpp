#ifndef ast_integer_hpp
#define ast_integer_hpp

#include "ast_node.hpp"

class Integer
  : public Node
{
private:
  int value;

public:
  // Constructor
  Integer(int _value)
    : value(_value)
  {}

  Integer() // Default initializer
    : Integer(0)
  {}

  // Useful shit (probs)
  int getValue() const
  {
    return value;
  }

  // Visualising
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override
  {
      dst << indent << "Integer = " << value << std::endl;
  }
};

#endif
