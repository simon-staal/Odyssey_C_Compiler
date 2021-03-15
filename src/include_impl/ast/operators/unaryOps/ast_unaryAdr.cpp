#include "ast/operators/unaryOps/ast_unaryAdr.hpp"

void UnaryAdr::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Unary Adr [ " << std::endl;
  dst << indent << "Op:" << std::endl;
  GetOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}


