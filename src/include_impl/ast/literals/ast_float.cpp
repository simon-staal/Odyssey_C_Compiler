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
void Float::generateMIPS(std::ostream &dst, Context &context, int destReg) const // I don't think we'll ever call this?
{
  // Loads immediate into floating point register (move back to other regs seperately)
  dst << "li.s $f" << destReg << ", " << value << std::endl;
}

void Float::generateTypeMIPS(std::ostream &dst, Context &context, int destReg, enum Specifier type) const
{
  switch(type){
    case _float:
      dst << "li.s $f" << destReg << ", " << value << std::endl;
      break;
    case _double:
      dst << "li.s $f" << destReg << ", " << value << std::endl;
      dst << "cvt.d.s $f" << destReg << ", $f" << destReg << std::endl; // Converts to double
      break;
    default:
      std::cerr << "Generating float but type isn't float or double" << std::endl;
      exit(1);
  }
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
