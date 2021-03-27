#include "ast/operators/unaryOps/ast_unaryAdr.hpp"

void UnaryAdr::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Unary Adr [ " << std::endl;
  dst << indent << "Op:" << std::endl;
  GetOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}


void UnaryAdr::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  //find variable you are &ing
  std::string id = GetOp()->getId();
  variable var;

  auto it = context.stack.back().varBindings.find(id);
  if( it == context.stack.back().varBindings.end() ){
    std::cerr << "Uninitialised Variable?" << std::endl;
  }else{
    var = it->second;
  }

  //put its address in destReg
  dst << "add $" << destReg << ", $30, " << var.offset << std::endl;

}
