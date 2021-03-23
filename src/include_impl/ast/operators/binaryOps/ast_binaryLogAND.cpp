#include "ast/operators/binaryOps/ast_binaryLogAND.hpp"

void BinaryLogAND::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Binary Logical AND [ " << std::endl;
  dst << indent << "Left Op:" << std::endl;
  LeftOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "Right Op: " << std::endl;
  RightOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}

void BinaryLogAND::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  
  int regLeft = DoLeft(dst, context, destReg);
  int regRight = DoRight(dst, context, destReg, regLeft);

  dst << "slti $" << regLeft << ", $" << regLeft << ", 1" << std::endl;
  dst << "slti $" << regRight << ", $" << regRight << ", 1" << std::endl;
  EZPrint(dst, "or", regLeft, regLeft, regRight);

  dst << "slti $" << destReg << ", $" << regLeft << ", 1" << std::endl;

  context.regFile.freeReg(regLeft);
  context.regFile.freeReg(regRight);
}
 
