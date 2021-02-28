#ifndef ast_primitives_hpp
#define ast_primitives_hpp

#include "ast_node.hpp"

class Constant
  : public Node
{
private:
  int value;
public:
  Constant(int _value)
    : value(_value)
  {}

  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override
  {
      dst << indent << "Constant = " << value << std::endl;
  }
}

#endif
