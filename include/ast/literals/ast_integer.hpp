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
  void PrettyPrint(std::ostream &dst, std::string indent) const override;

  // Codegen + helpers
  void generateMIPS(std::ostream &dst, Context &context, int destReg) const override;
  int getValue() const override; //needed for arrays
  int getSize() const override; // getsize stuff

};

#endif
