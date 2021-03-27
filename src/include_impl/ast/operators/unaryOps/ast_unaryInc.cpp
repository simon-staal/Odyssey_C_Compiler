#include "ast/operators/unaryOps/ast_unaryInc.hpp"

void UnaryInc::PrettyPrint(std::ostream &dst, std::string indent) const
{
  dst << indent << "Unary Inc [ " << std::endl;
  dst << indent << "Op:" << std::endl;
  GetOp()->PrettyPrint(dst, indent+"  ");
  std::cout << indent << "]" <<std::endl;
}

void UnaryInc::generateMIPS(std::ostream &dst, Context &context, int destReg) const
{
  std::string id = GetOp()->getId();
  variable op;

  auto it = context.stack.back().varBindings.find(id);
  if( it == context.stack.back().varBindings.end() ){
    std::cerr << "Inc a non var?" << std::endl;
  }else{
    op = it->second;
  }

  if(op.reg == -1){

    dst << "lw $" << destReg << ", " << op.offset << "($30)" << std::endl;
    dst << "addiu $" << destReg << ", $" << destReg << ", 1" << std::endl;
    dst << "sw $" << destReg << ", " << op.offset << "($30)" << std::endl;


  }else{

    dst << "addiu $" << op.reg << ", $" << op.reg << ", +1" << std::endl;
    dst << "sw $" << op.reg << ", " << op.offset << "($30)" << std::endl;
    dst << "move $" << destReg << ", $" << op.reg << std::endl;


  }
}
