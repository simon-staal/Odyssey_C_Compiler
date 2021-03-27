#include "ast/operators/unaryOps/ast_unaryBWNOT.hpp"

void UnaryBWNOT::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Unary BWNOT [ " << std::endl;
  dst << indent << "Op:" << std::endl;
  getOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}


void UnaryBWNOT::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{

  getOp()->generateMIPS(dst, context, destReg);

  ifFunction(dst, context, destReg);

  int reg = context.allocate();
  dst << "li $" << reg << ", -1" << std::endl;

  dst << "xor $" << destReg << ", $" << destReg << ", $" << reg << std::endl;

}
