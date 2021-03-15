#include "ast/operators/unaryOps/ast_unarySub.hpp"

void UnarySub::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Unary Sub [ " << std::endl;
  dst << indent << "Op:" << std::endl;
  GetOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}


