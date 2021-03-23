#include "ast/operators/binaryOps/ast_binaryNormalAss.hpp"

void BinaryNormalAss::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Binary NormalAss [ " << std::endl;
  dst << indent << "Left Op:" << std::endl;
  LeftOp()->PrettyPrint(dst, indent+ "  ");
  std::cout << indent << "Right Op: " << std::endl;
  RightOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}


void BinaryNormalAss::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{

  variable Var = LeftVar(context);

  RightOp()->generateMIPS(dst, context, destReg);

  AssEnd(dst, context, destReg, Var);

}
