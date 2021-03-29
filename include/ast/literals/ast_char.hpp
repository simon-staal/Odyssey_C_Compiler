#ifndef ast_char_hpp
#define ast_char_hpp

#include "ast/ast_node.hpp"

class Char
  : public Node
{
private:
  int value; // Using int so we can reuse all the getValue methods (and just use lsb)

public:
  // Constructor
  Char(int _value);

  // Visualising
  void PrettyPrint(std::ostream &dst, std::string indent) const override;

  // Codegen + helpers
  void generateTypeMIPS(std::ostream &dst, Context &context, int destReg, enum Specifier type) const override;
  int getValue() const override; //needed for arrays
  int getSize() const override; // getsize stuff
};

#endif
