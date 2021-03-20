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
  int regLeft, regRight;
  if( ((regLeft = context.regFile.allocate()) == -1) |  ((regRight = context.regFile.allocate()) == -1) ){
    std::cerr << "OOPSIES NO REGS ARE FREE. OVERWRITING" << std::endl;
  }

  LeftOp()->generateMIPS(dst, context, regLeft);
  RightOp()->generateMIPS(dst, context, regRight);

  std::cout << "div $" << regLeft << ", $" << regRight << std::endl;

  std::cout << "mflo $" << destReg << std::endl;

  context.regFile.freeReg(regLeft);
  context.regFile.freeReg(regRight);
}
 
