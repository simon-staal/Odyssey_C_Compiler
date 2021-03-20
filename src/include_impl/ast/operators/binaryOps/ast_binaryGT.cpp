#include "ast/operators/binaryOps/ast_binaryGT.hpp"

void BinaryGT::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Binary Greater Than [ " << std::endl;
  dst << indent << "Left Op:" << std::endl;
  LeftOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "Right Op: " << std::endl;
  RightOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}

void BinaryGT::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  int regLeft, regRight;
  if( ((regLeft = context.regFile.allocate()) == -1) |  ((regRight = context.regFile.allocate()) == -1) ){
    std::cerr << "OOPSIES NO REGS ARE FREE. OVERWRITING" << std::endl;
  }

  LeftOp()->generateMIPS(dst, context, regLeft);
  RightOp()->generateMIPS(dst, context, regRight);

  EZPrint(dst, "slt", destReg, regRight, regLeft);

  context.regFile.freeReg(regLeft);
  context.regFile.freeReg(regRight);
}
 
