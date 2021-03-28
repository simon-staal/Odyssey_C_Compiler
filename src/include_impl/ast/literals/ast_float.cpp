#include "ast/literals/ast_float.hpp"

// Constructors
Float::Float(double _value)
  : value(_value)
{}

// Visualising
void Float::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Float = " << value << std::endl;
}

// Codegen + helpers
void Float::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  // Loads immediate into floating point register (move back to other regs seperately)
  dst << "li.s $f" << destReg << ", " << value << std::endl;
}

void Float::generateTypeMIPS(std::ostream &dst, Context &context, int destReg, enum Specifier type) const
{
  dst << "li.s $f" << destReg << ", " << value << std::endl;
  dst << "cvt.d.s $f" << destReg << ", $f" << destReg << std::endl; // Converts to double
}

double Float::getFloat() const
{
  return value;
}

int Float::getSize() const
{
  std::cerr << "WARNING: CALLING GETSIZE ON FLOAT LITERAL" << std::endl;
  return 4;
}
