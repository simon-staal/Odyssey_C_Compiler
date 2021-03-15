#include "ast/operators/unaryOps/ast_unaryNOT.hpp"

void UnaryNOT::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Unary NOT [ " << std::endl;
  dst << indent << "Op:" << std::endl;
  GetOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}


