#include "ast/operators/unaryOps/ast_unaryPreInc.hpp"

void UnaryPreInc::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Unary Pre Inc [ " << std::endl;
  dst << indent << "Op:" << std::endl;
  GetOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}

