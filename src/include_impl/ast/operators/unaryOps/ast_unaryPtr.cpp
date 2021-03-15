#include "ast/operators/unaryOps/ast_unaryPtr.hpp"

void UnaryPtr::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Unary Ptr [ " << std::endl;
  dst << indent << "Op:" << std::endl;
  GetOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}


