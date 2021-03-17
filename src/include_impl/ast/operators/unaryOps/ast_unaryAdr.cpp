#include "ast/operators/unaryOps/ast_unaryAdr.hpp"

void UnaryAdr::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Unary Adr [ " << std::endl;
  dst << indent << "Op:" << std::endl;
  GetOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}


void UnaryAdr::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  int reg;
  if( (reg = context.regFile.allocate()) == -1){
    std::cerr << "OOPSIES NO REGS ARE FREE. OVERWRITING" << std::endl;
  }

  GetOp()->generateMIPS(dst, context, reg);

  dst << "sub $" << destReg << ", $0, " << reg << std::endl; 

  context.regFile.freeReg(reg);
}
