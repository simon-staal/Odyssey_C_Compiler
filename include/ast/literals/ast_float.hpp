#ifndef ast_float_hpp
#define ast_float_hpp

#include "ast/ast_node.hpp"

class Float
  : public Node
{
private:
  double value; // Using doubles by default, will convert to single precision if type is float when generating MIPS

public:
  // Constructors
  Float(double _value);

  // Visualising
  void PrettyPrint(std::ostream &dst, std::string indent) const override;

  // Codegen + helpers
  void generateMIPS(std::ostream &dst, Context &context, int destReg) const override;
  void generateTypeMIPS(std::ostream &dst, Context &context, int destReg, enum Specifier type) const;
  double getFloat() const override; //needed for arrays
  int getSize() const override; // getsize stuff
};

#endif
