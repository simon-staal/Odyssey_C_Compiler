#include "ast/operators/binaryOps/ast_binaryMul.hpp"

void BinaryMul::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Binary Multiplication [ " << std::endl;
  dst << indent << "Left Op:" << std::endl;
  LeftOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "Right Op: " << std::endl;
  RightOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}

void BinaryMul::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  
  int regLeft = DoLeft(dst, context, destReg);
  int regRight = DoRight(dst, context, destReg, regLeft);

  dst << "mult $" << regLeft << ", $" << regRight << std::endl;

  dst << "mflo $" << destReg << std::endl;

  context.regFile.freeReg(regLeft);
  context.regFile.freeReg(regRight);
}
 
void BinaryMul::generateTypeMIPS(std::ostream &dst, Context &context, int destReg, enum Specifier type) const
{
  switch(type)
  {
    case _ptr:
    {
      std::cerr << "multiplying pointers are we?" << std::endl;
    }
    case _float:
    {
      int regLeft = DoTypeLeft(dst, context, destReg, type);
      int regRight = DoTypeRight(dst, context, destReg, regLeft, type);

      dst << "mul.s $f" << destReg << ", $f" << regLeft << ", $f" << regRight << std::endl;

      context.floatRegs.freeReg(regLeft);
      context.floatRegs.freeReg(regRight);

      break;
    }
    
    case _double:
    {
      int regLeft = DoTypeLeft(dst, context, destReg, type);
      int regRight = DoTypeRight(dst, context, destReg, regLeft, type);

      dst << "mul.d $f" << destReg << ", $f" << regLeft << ", $f" << regRight << std::endl;

      context.floatRegs.freeReg(regLeft);
      context.floatRegs.freeReg(regRight);

      break;

    }

  }
}
