#include "ast/operators/binaryOps/ast_binaryEQ.hpp"

void BinaryEQ::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Binary Equal? [ " << std::endl;
  dst << indent << "Left Op:" << std::endl;
  LeftOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "Right Op: " << std::endl;
  RightOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}

void BinaryEQ::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  int regLeft, regRight;
  if( ((regLeft = context.regFile.allocate()) == -1) |  ((regRight = context.regFile.allocate()) == -1) ){
    std::cerr << "OOPSIES NO REGS ARE FREE. OVERWRITING" << std::endl;
  }

  LeftOp()->generateMIPS(dst, context, regLeft);
  RightOp()->generateMIPS(dst, context, regRight);

  EZPrint(dst, "xor", destReg, regLeft, regRight);

  std::cout << "sltiu $" << destReg << ", $" << destReg << ", 1" << std::endl; 

  context.regFile.freeReg(regLeft);
  context.regFile.freeReg(regRight);
}
 
