#include "ast/operators/unaryOps/ast_unaryAdr.hpp"
#include <cmath>

void UnaryAdr::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Unary Adr [ " << std::endl;
  dst << indent << "Op:" << std::endl;
  getOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}


void UnaryAdr::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  //find variable you are &ing
  std::string id = getOp()->getId();
  variable var;

  auto it = context.stack.back().varBindings.find(id);
  if( it == context.stack.back().varBindings.end() ){
    std::cerr << "Uninitialised Variable?" << std::endl;
  }else{
    var = it->second;
  }

  if(getOp()->getNode(1) != NULL){ // array
    getOp()->getNode(1)->generateMIPS(dst, context, destReg);
    dst << "sll $" << destReg << ", $" << destReg << ", " << (int)log2(var.size) << std::endl;
    dst << "addi $" << destReg << ", $" << destReg << ", " << var.offset << std::endl;
    dst << "add $" << destReg << ", $" << destReg << ", $30" << std::endl;
  }else{

  //put its address in destReg
  dst << "addi $" << destReg << ", $30, " << var.offset << std::endl;
  }


}
