#ifndef ast_integer_hpp
#define ast_integer_hpp

#include "ast/ast_node.hpp"

class Integer
  : public Node
{
private:
  int value;

public:
  // Constructors
  Integer(int _value);
  Integer(); // Default initializer

  // Visualising
  virtual void PrettyPrint(std::ostream &dst, std::string indent) const override;

  // Codegen
  virtual void generateMIPS(std::ostream &dst, Context &context, int destReg) const override;

  //needed for arrays
  virtual int getValue() const override;

};

#endif
