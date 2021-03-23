#include "ast/operators/binaryOps/ast_binaryGTEQ.hpp"

void BinaryGTEQ::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Binary Greater Than or Equal [ " << std::endl;
  dst << indent << "Left Op:" << std::endl;
  LeftOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "Right Op: " << std::endl;
  RightOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}

void BinaryGTEQ::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{

  int regLeft = DoLeft(dst, context, destReg);
  int regRight = DoRight(dst, context, destReg, regLeft);
  
  EZPrint(dst, "sub", destReg, regLeft, regRight);
  EZPrint(dst, "slt", destReg, 0, destReg);


  context.regFile.freeReg(regLeft);
  context.regFile.freeReg(regRight);
}
 
