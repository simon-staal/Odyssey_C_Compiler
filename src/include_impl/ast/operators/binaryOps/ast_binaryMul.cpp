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
 
