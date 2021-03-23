#include "ast/operators/binaryOps/ast_binaryLTEQ.hpp"

void BinaryLTEQ::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Binary Less Than or Equal [ " << std::endl;
  dst << indent << "Left Op:" << std::endl;
  LeftOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "Right Op: " << std::endl;
  RightOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}

void BinaryLTEQ::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{

  int regLeft = DoLeft(dst, context, destReg);
  int regRight = DoRight(dst, context, destReg, regLeft);

  EZPrint(dst, "sub", destReg, regLeft, regRight);

  dst << "slti $" << destReg << ", $" << destReg << ", 1" << std::endl;

  context.regFile.freeReg(regRight);
}
 
