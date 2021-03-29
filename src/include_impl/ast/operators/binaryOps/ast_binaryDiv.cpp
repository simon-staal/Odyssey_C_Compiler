#include "ast/operators/binaryOps/ast_binaryDiv.hpp"

void BinaryDiv::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Binary Division [ " << std::endl;
  dst << indent << "Left Op:" << std::endl;
  LeftOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "Right Op: " << std::endl;
  RightOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}

void BinaryDiv::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  int regLeft = DoLeft(dst, context, destReg);
  int regRight = DoRight(dst, context, destReg, regLeft);

  dst << "div $" << regLeft << ", $" << regRight << std::endl;

  dst << "mflo $" << destReg << std::endl;

  context.regFile.freeReg(regLeft);
  context.regFile.freeReg(regRight);
}

void BinaryDiv::generateTypeMIPS(std::ostream &dst, Context &context, int destReg, enum Specifier type) const
{
  switch(type)
  {
    case _ptr:
    {
      std::cerr << "dividing> pointers are we?" << std::endl;
    }
    case _float:
    {
      int regLeft = DoTypeLeft(dst, context, destReg, type);
      int regRight = DoTypeRight(dst, context, destReg, regLeft, type);

      dst << "div.s $f" << destReg << ", $f" << regLeft << ", $f" << regRight << std::endl;

      context.floatRegs.freeReg(regLeft);
      context.floatRegs.freeReg(regRight);

      break;
    }
    
    case _double:
    {
      int regLeft = DoTypeLeft(dst, context, destReg, type);
      int regRight = DoTypeRight(dst, context, destReg, regLeft, type);

      dst << "div.d $f" << destReg << ", $f" << regLeft << ", $f" << regRight << std::endl;

      context.floatRegs.freeReg(regLeft);
      context.floatRegs.freeReg(regRight);

      break;

    }

  }
}

 
