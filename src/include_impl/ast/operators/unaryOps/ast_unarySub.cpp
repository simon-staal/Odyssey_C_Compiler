#include "ast/operators/unaryOps/ast_unarySub.hpp"

void UnarySub::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Unary Sub [ " << std::endl;
  dst << indent << "Op:" << std::endl;
  getOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}

void UnarySub::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{

  getOp()->generateMIPS(dst, context, destReg);

  ifFunction(dst, context, destReg);

  dst << "sub $" << destReg << ", $0, $" << destReg << std::endl; 

}
