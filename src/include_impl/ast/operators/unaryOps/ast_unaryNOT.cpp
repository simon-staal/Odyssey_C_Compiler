#include "ast/operators/unaryOps/ast_unaryNOT.hpp"

void UnaryNOT::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Unary NOT [ " << std::endl;
  dst << indent << "Op:" << std::endl;
  GetOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}


void UnaryNOT::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{

  GetOp()->generateMIPS(dst, context, destReg);

  dst << "slti $" << destReg << ", $" << destReg << ", 1" << std::endl; 

  context.regFile.freeReg(reg);
}
