#include "ast/operators/unaryOps/ast_unaryPreDec.hpp"

void UnaryPreDec::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Unary Pre Dec [ " << std::endl;
  dst << indent << "Op:" << std::endl;
  GetOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}

