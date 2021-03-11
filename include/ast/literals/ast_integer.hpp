#ifndef ast_integer_hpp
#define ast_integer_hpp

#include "ast/ast_node.hpp"

class Integer
  : public Node
{
private:
  int value;

public:
  // Constructor
  Integer(int _value);

  Integer(); // Default initializer

  // Useful shit (probs)
  int getValue() const;

  // Visualising
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;
};

#endif
