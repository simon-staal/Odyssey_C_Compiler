#include "ast/operators/unaryOps/ast_unaryAdd.hpp"

void UnaryAdd::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Unary Addition [ " << std::endl;
  dst << indent << "Op:" << std::endl;
  GetOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}

void UnaryAdd::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{

  GetOp()->generateMIPS(dst, context, destReg);

}