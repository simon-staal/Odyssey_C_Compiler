#include "ast/operators/unaryOps/ast_unaryNOT.hpp"

void UnaryNOT::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Unary NOT [ " << std::endl;
  dst << indent << "Op:" << std::endl;
  getOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}


void UnaryNOT::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{

  getOp()->generateMIPS(dst, context, destReg);

  ifFunction(dst, context, destReg);

  dst << "slti $" << destReg << ", $" << destReg << ", 1" << std::endl; 

}
