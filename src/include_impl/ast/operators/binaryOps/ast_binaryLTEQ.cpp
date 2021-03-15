#include "ast/operators/binaryOps/ast_binaryLTEQ.hpp"

void BinaryLTEQ::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Binary Less Than or Equal [ " << std::endl;
  dst << indent << "Left Op:" << std::endl;
  LeftOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "Right Op: " << std::endl;
  RightOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}