#include "ast/operators/unaryOps/ast_unaryBWNOT.hpp"

void UnaryBWNOT::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Unary BWNOT [ " << std::endl;
  dst << indent << "Op:" << std::endl;
  GetOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}


